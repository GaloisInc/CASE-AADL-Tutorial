So You Want To Describe Some Data
=================================

Data in AADL is represented using the `data` component category, along with
properties from the standard `Data_Model` library (also refered to as the Data
Annex, or DAnnex). Together, these allow you to represent scalar types,
arrays, records / structures, unions, and enumerations.

(NOTE: What about network protocols? I don't really see a good way to
represent TLV protocols, for example, since we can't refer to a value within a
type. I.e., how would you indicate that one field of a record is a tag that
determines which element of a following union is present, or that the length
of an array is determined by a value given at the start? Do we just need to
punt to ASN1 in this case? Alternatively, could we represent these constraints
using REAL or AGREE properties?)

Scalar Types
------------

### Using types from `Base_Types`

Many scalar types are already defined for you in the
[`Base_Types`](https://github.com/OpenAADL/ocarina/blob/master/resources/AADLv2/base_types.aadl)
package. These include 8-, 16-, 32-, and 64-bit signed and unsigned integers;
single- and double-precision IEE754 floating-point numbers; characters; and
strings. For example, a light sensor might periodically output 16-bit unsigned
integer:

```aadl
with Base_Types, Data_Model;

device Light_Sensor
features
    Light : out data port Base_Types::Unsigned_16;
end Light_Sensor;
```

### Extending scalar types with `Data_Model`

You can use properties from the `Data_Model` library to express additional
information about and constraints on your data. If you know, for example, that
the (fictional) LuxWorks light sensor always outputs values between 0 and
50000, and that the units represented are lx, you could express that as
follows:

```aadl
data LuxWorks_Data extends Base_Types::Unsigned_16
properties
    Data_Model::Integer_Range => (0 .. 50000);
    Data_Model::Measurement_Unit => "lx";
end LuxWorks_Data;

device LuxWorks_Light_Sensor extends Light_Sensor
features
    Light : refined to out data port LuxWorks_Data;
end LuxWorks_Light_Sensor;
```

The full range of properties provided by `Data_Model` is documented
[here](https://github.com/OpenAADL/ocarina/blob/master/resources/data_model.aadl).

### Fixed-point types

Fixed-point types are not present in `Base_Types`, but they are easy to
represent using properties from `Data_Model`. Setting the
`Data_Representation` property to `Fixed` indicates that a data component uses
fixed-point representation, and the `Data_Digits` and `Data_Scale` properties,
respectively, indicate its range and precision. Consider a servo that outputs
the voltage it receives from the battery within the range of 0 to 9400 volts,
and with a precision of `10**(-3)`:

```aadl
data Voltage_Data
properties
    Data_Model::Data_Representation => Fixed;
    Data_Model::Data_Digits => 7; -- xxxx.xxx
    Data_Model::Data_Scale => 3;  -- 10**(-3) precision

    Data_Model::Measurement_Unit => "v";
end Voltage_Data;

device Servo
features
    Actuate : in data port;
    Voltage : out data port Voltage_Data;
end Servo;
```

Records
-------

Composite data with named fields are represented using the
`Data_Representation` value `Record`. The fields, along with their types are
represented as subcomponents. We might represent the output of an
accelerometer, for instance, as follows:

```aadl
data Acceleration
properties
    Data_Model::Data_Representation => Data_Model::Fixed;
    Data_Model::Data_Digits => 6;
    Data_Model::Data_Scale => 2;
    Data_Model::Measurement_Unit => "m/s^2";
end Acceleration;

data XYZ_Acceleration
properties
    Data_Model::Data_Representation => Data_Model::Struct;
end XYZ_Acceleration;

data implementation XYZ_Acceleration.Impl
subcomponents
    X : data Acceleration;
    Y : data Acceleration;
    Z : data Acceleration;
end XYZ_Acceleration.Impl;

device Accelerometer
features
    XYZ_Accel : out data port XYZ_Acceleration;
end Accelerometer;
```

(NOTE: There's also a DAnnex representation that uses just types, not
implementations, like the other data representations:

```aadl
data XYZ_Acceleration2
properties
    Data_Model::Data_Representation => Data_Model::Struct;
    Data_Model::Element_Names => ("X", "Y", "Z");
    Data_Model::Base_Type =>
       (classifier (Acceleration),
        classifier (Acceleration),
        classifier (Acceleration));
end XYZ_Acceleration2;
```

This is not very readable, but fits better with the other DAnnex
representations. Which one is better?)

Unions
------

(NOTE: I'm not sure these are actually useful. Tagged unions might be useful
to represent the "type" part of TLV structures, but that doesn't seem possible
using this construction.)

Sum types can be represented using properties from `Data_Model` as follows:

```aadl
data Either_Integer_Or_Float
properties
    Data_Model::Data_Representation => Data_Model::Union;
    Data_Model::Element_Names => ("The_Integer", "The_Float");
    Data_Model::Base_Type =>
       (classifier (Base_Types::Integer_32),
        classifier (Base_Types::Float_32));
end Either_Integer_Or_Float;
```

Arrays
------

Bounded and unbounded arrays can be represented using the `Array` value for
`Data_Representation` from the `Data_Model` property set. The underlying type
is represented using `Base_Type`, and the array bounds are given in
`Dimension`:

```aadl
data Array_Of_3_Integers
properties
    Data_Model::Data_Representation => Data_Model::Array;
    Data_Model::Base_Type => (classifier (Base_Types::Integer_32));
    Data_Model::Dimension => (3);
end Array_Of_3_Integers;
```

Unbounded arrays can be represented using the special `Dimension` value
`Infinite_Dimension`.

```aadl
data Unbounded_Array_Of_Integers
properties
    Data_Model::Data_Representation => Data_Model::Array;
    Data_Model::Base_Type => (classifier (Base_Types::Integer_32));
    Data_Model::Dimension => (Infinite_Dimension);
end Unbounded_Array_Of_Integers;
```
