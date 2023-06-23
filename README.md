# CASE-AADL-Tutorial

As part of the [DARPA CASE](https://www.darpa.mil/program/cyber-assured-systems-engineering) program, tools were developed to aid system engineers in designing complex embedded computing systems with built-in cyber resiliency. This tutorial is intended for MBSE enthusiasts and professionals who want to learn about CASE tooling. The CASE tools use AADL as their language of choice. AADL or the [Architecture Analysis & Design Language](https://en.wikipedia.org/wiki/Architecture_Analysis_%26_Design_Language) was standardized by SAE and primarily developed by [SEI](https://www.sei.cmu.edu/our-work/projects/display.cfm?customel_datapageid_4050=191439,191439). Originally intended for the Avionics domain, it has been used for modeling embedded software. The language provides a high level abstraction for describing software components and the connections between them. AADL is extensible, and many annexes have been introduced throughout the years to model different modeling aspects like correctness, cybersecurity aspects, behavior extensions and more.

The two part tutorial is split between training users on how to model systems with AADL and using DARPA CASE tools. The book is divided into two volumes titled - "So You Want To AADL" and "Introduction to DARPA CASE Tooling". The tutorial does not aim to be complete but is instead a starting point that leaves the reader with enough exposure to begin their own modeling journey. No prior experience in the tools are assumed. The tutorial was written in markdown and can be compiled in pdf and html using the included build script.

## Volume I: So You Want To AADL (AADL-based Tooling for Cyber Resilience)

AADL beginners should start with the this volume. The chapters cover the basics and disparate modeling aspects including authentication, encryption, protocol modeling and message filtering and more. Along with AADL the tutorial uses the AGREE Annex that requires the use of the AGREE tool. More information [here](pandoc/preface-aadl.md).

### Tutorial Requirements

  The tutorial has been tested on [OSATE 2.10.2](https://osate.org/). The only other dependency is AGREE and its tested version is discussed in the [following table](#volume-ii-introduction-to-darpa-case-tooling-aadl-based-tooling-for-cyber-resilience). Some  useful references are included below.

- Eclipse: https://www.eclipse.org/
- The Eclipse Modeling Project: https://www.eclipse.org/modeling/
- Eclipse XText: https://www.eclipse.org/Xtext/
- AADL: http://www.openaadl.org/ and http://aadl.info/
- Ocarina: http://www.openaadl.org/ocarina.html

## Volume II:   Introduction to DARPA CASE Tooling (AADL-based Tooling for Cyber Resilience)
The second volume focuses on the [tools](#case-tools) developed on the DARPA CASE program. Tools that are private were omitted from this tutorial (namely GearCASE and BriefCASE). Each chapter is devoted to a tool and can be read out-of-order. More information on this volume can be found in the [preface](pandoc/preface-case.md).

### Tutorial Requirements

  The tutorial has been tested on [OSATE 2.10.2](https://osate.org/) and the tool versions mentioned in the below table.

| Tool | Version | Repository | Documentation | Developers (PI) |
|-|-|-|-|:-:|
| [BriefCASE](http://loonwerks.com/projects/case.html) | 0.8.0 | [GitHub](https://github.com/loonwerks/BriefCase) | <ul><li>[User Guide](https://github.com/loonwerks/formal-methods-workbench/blob/master/documentation/BriefCASE/Collins%20BriefCASE%20User%20Guide.pdf)</li><li>[Videos](http://loonwerks.com/projects/case.html)</li></ul> | [Collins/Loonwerks](https://github.com/loonwerks)<br>([Darren Cofer](mailto:Darren.Cofer@collins.com)) |
| [DCRYPPS](https://www.dollabs.com/project/dcryp) | March2022-v1 <br>(code is archived)| [Google Drive](https://drive.google.com/drive/folders/1Xx3ZN_gjjBAmGsiqrW3V6qls4QH9QQhW) | <ul><li>User guide included in the zip archive</li><li>[YouTube Video](https://www.youtube.com/watch?v=VLt8LTNhktg)</li></ul> | Vanderbilt/[DOLL Labs](https://www.dollabs.com/)<br>([Bob Laddaga](mailto:robert.laddaga@vanderbilt.edu)) |
| [RESOLUTE](http://loonwerks.com/publications/gacek2014hilt.html) | 3.0.0 | [GitHub](https://github.com/loonwerks/Resolute) | <ul><li>[List of publications](http://loonwerks.com/tools/resolute.html)</li></ul> | [Collins/Loonwerks](https://github.com/loonwerks)<br>([Darren Cofer](mailto:Darren.Cofer@collins.com)) |
| [AGREE](http://loonwerks.com/tools/agree.html) | 2.9.1 | [GitHub](https://github.com/loonwerks/AGREE) | <ul><li>[User Guide](https://github.com/loonwerks/AGREE/tree/master/com.rockwellcollins.atc.agree.doc/src-gen)</li><li>[Documentation repo](https://github.com/loonwerks/AGREE/tree/master/com.rockwellcollins.atc.agree.doc)</li></ul> | [Collins/Loonwerks](https://github.com/loonwerks)<br>([Darren Cofer](mailto:Darren.Cofer@collins.com)) |
| [VERDICT](https://ge-high-assurance.github.io/VERDICT/) | 1.7.3 | [GitHub](https://github.com/ge-high-assurance/VERDICT/) | <ul><li>[README](https://github.com/ge-high-assurance/VERDICT/blob/master/README.md)</li><li>[Docs](https://github.com/ge-high-assurance/VERDICT/tree/master/docs)</li><li>[Wiki](https://github.com/ge-high-assurance/VERDICT/wiki)</li></ul>| [GE](https://github.com/ge-high-assurance)/Uni. of Iowa<br>([Michael Durling](mailto:durling@ge.com)) |
| [HAMR](https://hamr.sireum.org/index.html) | 1.2022.07051018.a740565 | [GitHub](https://github.com/sireum/hamr-codegen) | <ul><li>[Documentation](https://hamr.sireum.org/hamr-doc/hamr-index.html)</li></ul> | Kansas State University/[SAnToS Lab](mailto:hamr@santoslab.org)<br>([John Hatcliff](mailto:hatcliff@ksu.edu))|

Related commercial/propritary tools that are worth mentioning but were not developed on the program include:
- [CAMET](https://www.adventiumlabs.com/camet-access-request)
- [STOOD](https://www.ellidiss.com/products/stood/)
- [AADL Inspector](https://www.ellidiss.com/products/aadl-inspector/)
