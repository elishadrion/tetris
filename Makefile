FILE = srd
DIR = tex_files
OPTIONS = -pdf -output-directory=$(DIR)

basic: $(FILE).tex
	pdflatex $(OPTIONS) $<

auto: $(FILE).tex
	latexmk $(OPTIONS) $<

view: $(DIR)/$(FILE).pdf
	evince $< &
