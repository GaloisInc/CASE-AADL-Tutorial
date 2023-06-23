So You Want To Reverse Engineer Your Existing System
=====================================================

So you have a reverse engineering project that you want to document in AADL,
but you're not sure where to start. One good choice is to start at the top:
Begin by enumerating the top-level components of your system and the
communication channels between them. Then enumerate the subcomponents and
connections of those, as you discover what they are, etc.

For example, suppose we're analyzing an unmanned aerial system. Perhaps we've
observed that the vehicle and the ground station communicate over IEEE 802.11,
and we have some Wireshark traces of the traffic between the two. We want to
start documenting the protocol(s) that the two use to communicate as we
decipher them.

Creating a Containing Component
-------------------------------

In the same way that the entrance point to a C program is a function called
main, most AADL tools want a standalone system implementation to use as the
entrypoint to your AADL project. This is an implementation of a system whose
type has no features. It doesn't matter what we call this system (make it
descriptive, preferably), but it must be *complete*, meaning it has no
communication ports, requires no bus accesses, etc. We might start with the
following type definition:

```aadl
system UAS
features
    none;
end UAS;
```

Note that the type `UAS` is empty. That's fine. It's only there to allow us to
have a corresponding implementation, which will contain and connect
all of our top-level components. We'll start with an abstract implementation
that does nothing but enumerate the top-level components that make up our
system.

```aadl
system implementation UAS.Abstr
subcomponents
    Ground_Station : abstract;
    Vehicle : abstract;

    Radio : bus;
connections
    none;
    -- We'll connect components together here in our concrete implementation
end UAS.Abstr;
```

Here, we've just added the obvious top-level components of the UAS&mdash;the
ground station and the vehicle&mdash;and the radio channel over which they
communicate. In a fully specified system, these would likely both be modelled
as `system` components to indicate that each has its own internal software and
hardware, but here we'll leave them as `abstract` to avoid tying ourselves to
a particular representation. We'll model the radio as a `bus`, though, since
that's the only component category that makes sense in this case.

Enumerating Subcomponents
-------------------------

The next thing we'd like to express is that both components are attached to
the bus. To do that, we first need to define types for our subcomponents in
order to express the external features they expose.

```aadl
bus IEEE80211
end IEEE80211;

system UAV
features
    Radio : requires bus access IEEE80211;

    UDP8080 : in data port;
    UDP8081 : in out data port;
    -- Additional communication ports
end UAV;

system GS
features
    Radio : requires bus access IEEE80211;

    UDP8080 : out data port;
    UDP8081 : in out data port;
    -- Additional communication ports
end GS;
```

The above indicates that the UAV and the GS both need access to the IEEE
802.11 bus, and begins to enumerate the communication ports observed between
the two. We can flesh out the format of the communication on these ports by
assigning a data component type or implementation to each port (see [Data
Descriptions](./data_descriptions.md)). But first, we'll create a more
concrete version of the containing system with the subcomponents we've
created, and connect them together.

```aadl
system implementation UAS.Concrete extends UAS.Abstr
subcomponents
    Ground_Station : refined to system GS;
    Vehicle : refined to system UAV;

    Radio : refined to bus IEEE80211;
connections
    bus access Radio -> Ground_Station.Radio;
    bus access Radio -> Vehicle.Radio;

    UDP8080 : port Ground_Station.UDP8080 -> Vehicle.UDP8080;
    UDP8081 : port Ground_Station.UDP8081 <-> Vehicle.UDP8081;
properties
    actual_connection_binding => (reference (Radio))
        applies to UDP8080, UDP8081;
end UAS.Concrete;
```

Implementing Subcomponents
--------------------------

At this point, we can begin to repeat the process of enumerating subcomponents
on our `UAV` and `GS` types. For example, we might begin enumerating the
subcomponents of UAV abstractly, just as we did for the containing system.

```aadl
system implementation UAV.Abstr
subcomponents
    Flight_Controller : abstract;
    Mission_Controller : abstract;
    IMU : abstract;
    Camera : abstract;

    Wifi_Modem : abstract;
    Ethernet : bus;

    -- Additional subcomponents;
end UAV.Abstr;
```

Next, we would fill in the concrete types of these subcomponents, and so on.
The eventual goal is to have a fully specified system, with no abstract
components or unimplemented component types.
