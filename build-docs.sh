#!/usr/bin/env bash

## NOTE: This script requires pandoc and pdflatex to be installed

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

makebook() {
  while read -r line; do
    # Remove leading and trailing spaces
    line=$(echo "$line" | tr -d '[:space:]')

    # Extract chapter name using regex
    if [[ $line =~ .*chapter([[:alnum:]_]+).* ]]; then
      chapter="${BASH_REMATCH[1]}"
    fi

    makedocs $line chapter$chapter
  done <<< "$1"
}

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

AADL_CHAPTERS="
  aadl_book/chapter1_aadl_basics
  aadl_book/chapter2_data_descriptions
  aadl_book/chapter3_reverse_engineer
  aadl_book/chapter4_filters
  aadl_book/chapter5_authentication
  aadl_book/chapter6_encryption
  aadl_book/chapter7_tagged_message_protocol
  aadl_book/chapter8_stateful_protocol
  aadl_book/chapter9_layer2_hub
"
#chapter5_resolute/README.md

CASE_CHAPTERS="
  case_book/chapter1_verdict
  case_book/chapter2_dcrypps
  case_book/chapter3_hamr
  case_book/chapter4_resolute
"

## Remove empty newlines
AADL_CHAPTERS=$(echo "$AADL_CHAPTERS" | sed -e 's/^[[:space:]]*//' -e 's/[[:space:]]*$//' -e '/^$/d')
CASE_CHAPTERS=$(echo "$CASE_CHAPTERS" | sed -e 's/^[[:space:]]*//' -e 's/[[:space:]]*$//' -e '/^$/d')

makebook "${AADL_CHAPTERS}"
makebook "${CASE_CHAPTERS}"

## Construct README.md paths
AADL_CHAPTERS_README=$(echo "$AADL_CHAPTERS" | sed 's|$|/README.md|')
CASE_CHAPTERS_README=$(echo "$CASE_CHAPTERS" | sed 's|$|/README.md|')

pandoc -s -f gfm \
  -V geometry:margin=1.8cm \
  -H ${PROJ_ROOT}/pandoc/style-code.tex \
  -o ${PROJ_ROOT}/docs/SoYouWantToAADL.pdf \
  --resource-path ${PROJ_ROOT}/pandoc:${PROJ_ROOT}/docs/html \
  --metadata-file ${PROJ_ROOT}/pandoc/meta-aadl.yaml \
  --number-sections \
  ${PROJ_ROOT}/pandoc/preface-aadl.md \
  ${AADL_CHAPTERS_README}

pandoc -s -f gfm \
  -V geometry:margin=1.8cm \
  -H ${PROJ_ROOT}/pandoc/style-code.tex \
  -o ${PROJ_ROOT}/docs/CASE-tools.pdf \
  --resource-path ${PROJ_ROOT}/pandoc:${PROJ_ROOT}/docs/html \
  --metadata-file ${PROJ_ROOT}/pandoc/meta-case.yaml \
  --number-sections \
  ${PROJ_ROOT}/pandoc/preface-case.md \
  ${CASE_CHAPTERS_README}
  #<(sed '1s/.*/Resolute Tutorial/' chapter5_resolute/README.md)

echo "Success: docs built in ${PROJ_ROOT}/docs/"
echo "To create a zip of this content, run:"
echo "  cd ${PROJ_ROOT}"
echo "  zip -r docs.zip docs"

# ## Generate single markdown for each book volumes.
# # pandoc -f gfm --toc -s ${AADL_CHAPTERS} -o ./aadl_book/README.md
# # pandoc -f gfm --toc -s ${CASE_CHAPTERS} -o ./case_book/README.md