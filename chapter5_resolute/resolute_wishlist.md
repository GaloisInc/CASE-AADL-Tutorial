Resolute Wishlist
=================

* `instanceof` errors out when called on a `flow_spec`, making it difficult to use the result of `flow_elements()`, since it is a list containing `flow_spec`, `connection`, and `component`.
* Why does `flow_elements` output a set, when the natural interperatation of a flow is an ordered sequence?
* There seems to be no way to reference constant properties.
* End-to-end flows apparently can't be specified in implementation Resolute annex blocks. For example, if `My_Flow` is an `end_to_end_flow` within the system implementation `My_System.I`, a Resolute block within `My_System.I` that references `this.My_Flow` will fail to find the flow.
