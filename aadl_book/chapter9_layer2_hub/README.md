Layer-2 Network Hub, or "So You Want To Model A Shared Hub / Bus"
=================================================================

Goal
----

Model a layer-2 broadcast domain with hub behavior. I.e., all frames
are visible to all parties, and frames are filtered by address at the NIC for
non-promiscuous nodes.

Ethernet Frames and NICs
------------------------

Our model of an ethernet frame is simplistic, but sufficient for our purposes.
The only data field will be an integer destination address:

```aadl
data Frame
end Frame;

data implementation Frame.Base
subcomponents
    Dst_Addr : data Base_Types::Natural;
end Frame.Base;
```

AGREE does not model bitwise operations, nor does it have hexadecimal
literals, so using realistic six-octet ethernet addresses would not be useful.
Instead, our addresses are simple positive numbers. Somewhat arbitrarily, zero
will be used as the broadcast address:

```aadl
annex agree {**
    const broadcast_addr : int = 0;
**};
```

A NIC has internal (`Send`, `Recv`) and external (`TX`, `RX`) ports for
sending and receiving frames, an address, and rules that pass frames between
the internal and external ports, filtering out incoming frames that have a
destination address other than the NIC's address or broadcast.

The NIC's address is expressed using an AADL property, so that it can be
assigned in the containing component implementation. Setting the
`Promiscuous` property to `true` causes the NIC to ignore the address filter.

```aadl
system NIC
features
    RX : in  event data port Frame.Base;
    TX : out event data port Frame.Base;

    Send : in  event data port Frame.Base;
    Recv : out event data port Frame.Base;
properties
    Eth_Properties::Address     => 0;
    Eth_Properties::Promiscuous => false;
annex agree {**
    guarantee "Relay sent data to TX" :
        event(TX) = event(Send) and TX = Send;
    guarantee "Filter recv'd data by address" :
        event(Recv) = filter_rx and Recv = RX;

    property filter_rx = event(RX) and (
        RX.Dst_Addr = Get_Property(this, Eth_Properties::Address) or
        RX.Dst_Addr = broadcast_addr
    ) or Get_Property(this, Eth_Properties::Promiscuous);
**};
end NIC;
```

The Hub
-------

We model a hub device as having a fixed number of switch-ports, each of which
consists of separate `RX` and `TX` AADL ports, allowing us to distinguish
between send and receive events.

The AGREE clause guarantees that a frame received on any `RX` port will
propagate to all `TX` ports. This raises a question: What should happen if
more than one receive event occurs at once? In a real system, the answer to
this would involve queueing. Although a small fixed-size queue can be modelled
in AGREE, it is cumbersome and error prone. If you need to model queueing
behavior, AGREE may not be the right tool for the job. For our purposes, a
simple four-way arbiter suffices.

```aadl
system Hub4
features
    RX0 : in  event data port Eth::Frame.Base;
    TX0 : out event data port Eth::Frame.Base;

    RX1 : in  event data port Eth::Frame.Base;
    TX1 : out event data port Eth::Frame.Base;

    RX2 : in  event data port Eth::Frame.Base;
    TX2 : out event data port Eth::Frame.Base;

    RX3 : in  event data port Eth::Frame.Base;
    TX3 : out event data port Eth::Frame.Base;
annex agree {**
    guarantee "TXed data is arbitrated RXed data" :
        event(TX0) = in_event and TX0 = arbitrated_data and
        event(TX1) = in_event and TX1 = arbitrated_data and
        event(TX2) = in_event and TX2 = arbitrated_data and
        event(TX3) = in_event and TX3 = arbitrated_data;

    eq in_event : bool =
        event(RX0) or event(RX1) or event(RX2) or event(RX3);
    eq arbitrated_data : Eth::Frame.Base = -- Look Ma, no queueing!
        if event(RX0) then RX0 else
        if event(RX1) then RX1 else
        if event(RX2) then RX2 else
        if event(RX3) then RX3 else RX0;
**};
end Hub4;
```

Verification
------------

To use this implementation, we connect several NICs to a hub in a system
implementation. In a more sophisticated implementation, we might use a NIC as
a subcomponent of more complex node, but in this case we will just use bare
NICs.

The property we check says that any frame that appears on the internal side of
a NIC has a destination address that is either the address of the NIC or
broadcast:

```aadl
annex agree {**
    guarantee "TXed data is arbitrated RXed data" :
        event(TX0) = in_event and TX0 = arbitrated_data and
        event(TX1) = in_event and TX1 = arbitrated_data and
        event(TX2) = in_event and TX2 = arbitrated_data and
        event(TX3) = in_event and TX3 = arbitrated_data;

    eq in_event : bool =
        event(RX0) or event(RX1) or event(RX2) or event(RX3);
    eq arbitrated_data : Eth::Frame.Base = -- Look Ma, no queueing!
        if event(RX0) then RX0 else
        if event(RX1) then RX1 else
        if event(RX2) then RX2 else
        if event(RX3) then RX3 else RX0;
**};
```

This property (in `Complete.Hubbed`) should pass, when `Verify all layers` is
run on it. This is due to the filtering performed in our NIC. It *doesn't*
mean that frames with other addresses are invisible to the external side of
the NIC. We can see this by extending our implementation to make one of the
NICs promiscuous:

```aadl
system implementation Complete.Hubbed_Promisc extends Complete.Hubbed
properties
    Eth_Properties::Promiscuous => true applies to NIC1;
end Complete.Hubbed_Promisc;
```

Running "Verify all layers" on `Complete.Hubbed_Promisc` should yield a
counterexample.
