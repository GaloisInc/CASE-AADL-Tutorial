Preface
=======

This document contains our training material aimed at teaching users how to
model systems with AADL in preparation for using the DARPA CASE tools. It is
structured as follows: Chapters 2 and 3 comprise a succinct primer to the AADL
language . Every subsequent chapter is a goal-oriented example of using AADL.
Each one starts by describing a modeling goal a user might wish to achieve and a
system to be modeled. We then talk the user through the process of creating a
model, performing the desired analysis, and in some cases, evolving the model
and system design based on the results. The idea is that users can jump directly
to the chapters relevant to them, then pick which ideas from that chapter to
apply to their own model. Many of the modeling goals and systems chosen in our
chapters are based on conversations with Lockheed Martin.

We began this documentation project with a few objectives in mind: First, we
want to enable users who might be unfamiliar with AADL, and even with system
modeling, to create a working model of their system as quickly as possible.
Second, we want the models our users create to be practical and scoped
appropriately for specific analysis they wish to perform. And finally, we want
to ensure that our users are exposed to every aspect of AADL necessary to use
the CASE tooling.

Getting users started quickly guided our decision to structure our training
material as a series of examples. Several resources exist for those who want to
learn every detail of the AADL language (notably, "Model-Based Engineering with
AADL", by Feiler and Gluch), and we do not wish to replicate this work.
Instead, we want users to be able to pick the chapters relevant to their system
and create their own models by example. We have tried to make the reasoning
that guided our modeling choices in each example clear to help users do this in
an informed way and learn about AADL and modeling in the process.

A common pitfall is to model a system at too fine or too coarse a granularity.
For this reason, each of our examples is scoped to a particular analysis task,
and we have tried to be explicit about which system elements we have chosen to
or not to include and why. We hope this helps users think about the scope of
their own models, bearing in mind the analyses they would like to perform. Our
choice of examples and systems to model was guided by discussions with
cyber-physical-system designers.

Lastly, to ensure that users are thoroughly prepared to use the CASE tools, we
focus on the AADL features and extensions relevant to those tools.  Rather than
aiming for breadth in our coverage of AADL language features, we stick to the
ones employed by the CASE tools (systems, processes, threads, busses, and data
ports, primarily). In addition, we cover the main annexes used by the CASE
tools, namely AGREE and the Data Annex.

We believe this document will be effective in giving users a firm foundation on
how to model cyber-physical systems in AADL. Moreover, it gives users all the
information they need to take advantage of our "Introduction to DARPA CASE
Tooling" and begin applying AADL modeling and the CASE tools to their own
systems.
