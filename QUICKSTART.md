# VM Contents and Tool Versions

  The VM includes tools developed as part of DARPA CASE program and [OSATE 2.10.2](https://osate.org/).

| Tool | Version | Repository | Documentation | Developers |
|-|-|-|-|:-:|
| [BriefCASE](http://loonwerks.com/projects/case.html) | 0.8.0 | [GitHub](https://github.com/loonwerks/BriefCase) | <ul><li>[User Guide](https://github.com/loonwerks/formal-methods-workbench/blob/master/documentation/BriefCASE/Collins%20BriefCASE%20User%20Guide.pdf)<br>VM location: `~/Tools/BriefCASE/`<li></li>[Videos](http://loonwerks.com/projects/case.html)</li></ul> | [Collins/Loonwerks](https://github.com/loonwerks) (PI: [Darren Cofer](mailto:Darren.Cofer@collins.com)) |
| [GearCASE](#gearcase) | 2.4.0 (build 202205122047) | Private | <ul><li>Private<br>VM location: `~/Tools/GearCASE/`</li></ul> | Charles River Analytics (PI: [Terry Patten](mailto:tpatten@cra.com)) |
| [DCRYPPS](https://www.dollabs.com/project/dcryp) | March2022-v1 | Private | <ul><li>Private<br>VM location: `~/Tools/DCRYPPS/`<li></li>[YouTube Video](https://www.youtube.com/watch?v=VLt8LTNhktg)</li></ul> | Vanderbilt/[Dollabs](https://www.dollabs.com/) (PI: [Bob Laddaga](mailto:robert.laddaga@vanderbilt.edu)) |
| [RESOLUTE](http://loonwerks.com/publications/gacek2014hilt.html) | 3.0.0 | [GitHub](https://github.com/loonwerks/Resolute) | <ul><li>[List of publications](http://loonwerks.com/tools/resolute.html)</li></ul> | [Collins/Loonwerks](https://github.com/loonwerks) (PI: [Darren Cofer](mailto:Darren.Cofer@collins.com)) |
| [AGREE](http://loonwerks.com/tools/agree.html) | 2.9.1 | [GitHub](https://github.com/loonwerks/AGREE) | <ul><li>[User Guide](https://github.com/loonwerks/AGREE/tree/master/com.rockwellcollins.atc.agree.doc/src-gen)</li><li>[Documentation repo](https://github.com/loonwerks/AGREE/tree/master/com.rockwellcollins.atc.agree.doc)</li></ul> | [Collins/Loonwerks](https://github.com/loonwerks) (PI: [Darren Cofer](mailto:Darren.Cofer@collins.com)) |
| [VERDICT](https://ge-high-assurance.github.io/VERDICT/) | 1.7.3 | [GitHub](https://github.com/ge-high-assurance/VERDICT/) | <ul><li>[README](https://github.com/ge-high-assurance/VERDICT/blob/master/README.md)</li><li>[Docs](https://github.com/ge-high-assurance/VERDICT/tree/master/docs)</li><li>[Wiki](https://github.com/ge-high-assurance/VERDICT/wiki)</li></ul>| [GE](https://github.com/ge-high-assurance)/University of Iowa (PI: [Michael Durling](mailto:durling@ge.com)) |
| [HAMR](https://hamr.sireum.org/index.html) | 1.2022.07051018.a740565 | [GitHub](https://github.com/sireum/hamr-codegen) | <ul><li>[hamr.sireum.org](https://hamr.sireum.org/hamr-doc/ch00-hamr-overview.html)</li></ul> | [hamr@santoslab.org](mailto:hamr@santoslab.org) |
| [CAMET](https://www.adventiumlabs.com/camet) | 1.2.1 | Private | <ul><li>Private<br>VM location: `~/home/aadl/Tools/Osate2.10.2/plugin-source/camet/documentation`</li></ul>  | [Adventium Labs](https://www.adventiumlabs.com/) |

# Steps to Configure the VM

## Import the VM

The AADL tools VM is distributed as an Open Virtual Appliance file called
`tools.ova`. This file can be imported into a virtualization platform such as
VMWare Player or VirtualBox. To import the appliance into VirtualBox, follow
these
[instructions](https://docs.oracle.com/cd/E26217_01/E26796/html/qs-import-vm.html).
Once imported, login with the username `aadl` and password `aadl_tools`.

**NOTE**: By default, the VM is configured with 16GB of RAM. This setting may
need to be manually adjusted if it cannot be supported by the host OS. Overprovisioning 
VM memory may lead to VM crashes. 

## Launch Osate

  1. From a terminal, `cd ~/Tools/Osate2.10.2`
  2. `./osate`
  3. We suggest using the default workspace, and click launch

## Configure VERDICT

Launch OSATE, go to the `Window > Preferences` menu then look for the `Verdict > Verdict Settings` preferences pane, and fill out the following two fields:

1. Click the "Browse..." button next to the "STEM Project PATH:" field and navigate to `/home/aadl/Tools/Osate2.10.2/plugin-source/verdict/extern/STEM`
2. Click within the "`Bundle Docker Image:`" field and enter `gehighassurance/verdict:<x.y.z>`

Save your changes by clicking the "`Apply and Close`" button.

## Test an Example Project

1. Import an example project into OSATE by selecting `File > Import...`, select `General > Projects from Folder or Archive`, then click "`Next`".
2. Under "Import source", select directory `/home/aadl/Tools/Osate2.10.2/plugin-source/verdict/extern/examples/DeliveryDrone` and then click "`Finish`".
3. Under the "AADL Navigator" single-click on the newly imported "DeliveryDrone" project.
4. Select the `Verdict > Run Model Based Architecture Analysis (MBAA)` menu item and verify that the analysis completes without error. A successful run of Verdict on this example will report "mission failed" with two failed analysis results, indicating the places in the DeliveryDrone example where mitigations are needed to satify the specified cyber requirements.
5. You are now ready to analyze AADL models with the OSATE toolchain!

## Launch DECRYPPS

1. From a terminal `cd ~/Tools/DCRYPPS`
2. `./start_dcrypps.sh`
3. After the script completes, navigate to `http://localhost:8888` in a web browser and validate that the WebGME page is loaded.
4. You are now ready to analyze AADL models with DCRYPSS!
