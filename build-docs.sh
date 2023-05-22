#!/usr/bin/env bash

# NOTE: This script requires pandoc and pdflatex to be installed

set -e

PROJ_ROOT=$(git rev-parse --show-toplevel)

PDF_CMD="pandoc \
    -H ${PROJ_ROOT}/pandoc/style-headings.tex \
    -H ${PROJ_ROOT}/pandoc/style-code.tex \
    -s -f gfm \
    -V papersize:letter \
    -V geometry:margin=1.8cm"

HTML_CMD="pandoc --css css/style.css -s -f gfm"

HTML_IMAGE_DIR=${PROJ_ROOT}/docs/html/images
HTML_ICON_DIR=${PROJ_ROOT}/docs/html/icons
HTML_FIGURES_DIR=${PROJ_ROOT}/docs/html/figures
HTML_CSS_DIR=${PROJ_ROOT}/docs/html/css

makedocs() {
  pushd ${PROJ_ROOT}/${1}
  ${PDF_CMD} ${3} -o ${2}.pdf README.md
  ${HTML_CMD} --metadata pagetitle=${2} -o ${2}.html -t html README.md
  mv ${2}.pdf ${PROJ_ROOT}/docs/pdf
  mv ${2}.html ${PROJ_ROOT}/docs/html

  if [[ -d "${PROJ_ROOT}/${1}/images" ]]
  then
    cp ${PROJ_ROOT}/${1}/images/* ${HTML_IMAGE_DIR}
  fi

  if [[ -d "${PROJ_ROOT}/${1}/icons" ]]
  then
    cp ${PROJ_ROOT}/${1}/icons/* ${HTML_ICON_DIR}
  fi

  if [[ -d "${PROJ_ROOT}/${1}/figures" ]]
  then
    cp ${PROJ_ROOT}/${1}/figures/* ${HTML_FIGURES_DIR}
  fi
  popd
}

rm -rf ${PROJ_ROOT}/docs
mkdir -p ${PROJ_ROOT}/docs
mkdir -p ${PROJ_ROOT}/docs/pdf
mkdir -p ${PROJ_ROOT}/docs/html
mkdir -p ${HTML_IMAGE_DIR}
mkdir -p ${HTML_ICON_DIR}
mkdir -p ${HTML_FIGURES_DIR}

mkdir -p ${HTML_CSS_DIR}
cp ${PROJ_ROOT}/pandoc/*.css ${HTML_CSS_DIR}


# Individual "So You Want To AADL" content

makedocs aadl_basics "01-So-You-Want-To-AADL"
makedocs data_descriptions "02-So-You-Want-To-Describe-Some-Data"
makedocs getting_started "03-So-You-Want-To-Reverse-Engineer-Your-Existing-System"
makedocs filters "04-So-You-Want-To-Validate-Your-Data"
makedocs authentication "05-So-You-Want-To-Talk-About-Authentication"
makedocs encryption "06-So-You-Want-To-Make-Sure-Your-Data-Is-Encrypted"
makedocs tagged_message_protocol "07-So-You-Want-To-Parse-Wire-Protocols"
makedocs stateful "08-So-You-Want-To-Model-A-Stateful-Protocol"
makedocs layer-2_hub "09-So-You-Want-To-Model-A-Shared-Hub"
makedocs resolute-drone "10-So-You-Want-To-Check-Your-SWaP-Math"


# Individual "CASE Tools" content

makedocs gnc "VERDICT-tutorial"
makedocs drone "DCRYPPS-tutorial"
makedocs camera_gearcase "GearCASE-tutorial" "-H ${PROJ_ROOT}/pandoc/extra-style.tex"
makedocs hamr "HAMR-tutorial"
makedocs resolute-drone "Resolute-tutorial"

# note: the Resolute tutorial is the resolute-drone/SWaP-Math chapter above


# Combined content

AADL_CHAPTERS="
  aadl_basics/README.md
  data_descriptions/README.md
  getting_started/README.md
  filters/README.md
  authentication/README.md
  encryption/README.md
  tagged_message_protocol/README.md
  stateful/README.md
  layer-2_hub/README.md
  resolute-drone/README.md
"

CASE_CHAPTERS="
  gnc/README.md
  drone/README.md
  camera_gearcase/README.md
  hamr/README.md
"
# NOTE: we also add the Resolute tutorial below, changing the AADL-book title
# inline to better match the other CASE chapters

pandoc -s -f gfm \
  -V geometry:margin=1.8cm \
  -H ${PROJ_ROOT}/pandoc/style-code.tex \
  -o ${PROJ_ROOT}/docs/SoYouWantToAADL.pdf \
  --resource-path ${PROJ_ROOT}/pandoc:${PROJ_ROOT}/docs/html \
  --metadata-file ${PROJ_ROOT}/pandoc/meta-aadl.yaml \
  --number-sections \
  ${PROJ_ROOT}/pandoc/preface-aadl.md \
  ${AADL_CHAPTERS}

pandoc -s -f gfm \
  -V geometry:margin=1.8cm \
  -H ${PROJ_ROOT}/pandoc/style-code.tex \
  -o ${PROJ_ROOT}/docs/CASE-tools.pdf \
  --resource-path ${PROJ_ROOT}/pandoc:${PROJ_ROOT}/docs/html \
  --metadata-file ${PROJ_ROOT}/pandoc/meta-case.yaml \
  --number-sections \
  ${PROJ_ROOT}/pandoc/preface-case.md \
  ${CASE_CHAPTERS} \
  <(sed '1s/.*/Resolute Tutorial/' resolute-drone/README.md)

echo "Success: docs built in ${PROJ_ROOT}/docs/"
echo "To create a zip of this content, run:"
echo "  cd ${PROJ_ROOT}"
echo "  zip -r docs.zip docs"
