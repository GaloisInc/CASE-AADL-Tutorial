AADL Tools
==========

OSATE and Related Tools
-----------------------

- Eclipse: https://www.eclipse.org/
- The Eclipse Modeling Project: https://www.eclipse.org/modeling/
- Eclipse XText: https://www.eclipse.org/Xtext/
- AADL: http://www.openaadl.org/ and http://aadl.info/
- Open Source Tools
  - OSATE: https://osate.org/
  - Ocarina: http://www.openaadl.org/ocarina.html
- Commercial/Propritary Tools
  - From Ellidiss: https://www.ellidiss.com/
    - STOOD: https://www.ellidiss.com/products/stood/
    - AADL Inspector: https://www.ellidiss.com/products/aadl-inspector/

CASE Tools
----------

| Tool | Category | Example chapter(s) |
|-|-|-|
| [AGREE](#agree) | behavioral modeling with compositional assume/guarantee reasoning | practically all of them |
| [VERDICT/CRV](#verdict) | requirements validation | gnc |
| [VERDICT/MBAS](#verdict) | requirements discovery | gnc |
| [GearCASE](#gearcase) | requirements discovery | camera_gearcase |
| [AWAS](#awas) | model visualization / flow analysis | N/A |

### <a id="agree"></a> AGREE

- Loonwerks repo: https://github.com/loonwerks/AGREE

### <a id="verdict"></a> VERDICT (MBAS/CRV)

- VERDICT repo: https://github.com/ge-high-assurance/VERDICT

### <a id="gearcase"></a> GearCASE

- Note: proprietary software (not publicly distributed)

### <a id="awas"></a> AWAS

- AWAS homepage: https://awas.sireum.org/

AWAS provides an alternative to OSATE's model visualization. AWAS represents
models as graphs with components as vertices and connections, bindings, etc. as
edges. When run on a model, the tool creates a visualization with a portable
HTML-based interface. The advantage of AWAS's visualizations provide over
OSATE's is that they contain more visual information about connections in the
model, including connection and flow information and hardware binding
relationships. In turn, they provide less visual information about the
components in the model. The AWAS visualization interface also contains a query
language that allows users to quickly identify connections matching various
criteria. For example, queries can be written to find all the components that
receive data (directly or indirectly) from a given port, all the data flows from
one component to another, etc.

Other Tools
-----------

| Tool | Category | Relevant chapter |
|-|-|-|
| [BLESS](#bless) | state-machine-based behavioral modeling with set-theoretic reasoning | none |
| [CHEDDAR](#cheddar) | timing analysis | none |
| [Data Annex](#da) | data description | data_descriptions |
| [Resolute](#res) | non-functional requirements | none |
| [REAL](#real) | non-functional requirements with set-theoretic reasoning | none |

### <a id="bless"></a> BLESS

- Official site: http://bless.santoslab.org/node/1
- Language reference: http://www.santoslab.org/pub/bless/docs/BLESS_Language_Reference_Manual.pdf
- Technical slides: http://www.santoslab.org/pub/bless/docs/BLESS%20Tutorial.pdf
- Tutorial: http://www.santoslab.org/pub/bless/simpleproof/simpleproof_tutorial.pdf

### <a id="cheddar"></a> CHEDDAR

- Official site: http://beru.univ-brest.fr/cheddar/

### <a id="da"></a> Data Annex

- Note: see our "Data Descriptions" chapter.

### <a id="res"></a> Resolute

- Official site: http://loonwerks.com/publications/gacek2014hilt.html

### <a id="real"></a> REAL: Requirements and Enforcements Analysis Language

- Relevant publication:
  > O. Gilles and J. Hugues, "Expressing and Enforcing User-Defined Constraints of AADL Models," 2010 15th IEEE International Conference on Engineering of Complex Computer Systems, 2010, pp. 337-342, doi: 10.1109/ICECCS.2010.26.
