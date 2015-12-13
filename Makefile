DIR = tex_files
FILE = $(DIR)/srd
OPTIONS = -pdf -output-directory=$(DIR)
PDF_V = evince			#open, okular, skim, adobe...

auto: $(FILE).tex
	latexmk $(OPTIONS) $<

basic: $(FILE).tex
	pdflatex $(OPTIONS) $<

view: $(FILE).pdf
	$(PDF_V) $< &
