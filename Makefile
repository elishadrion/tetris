FILE = srd
DIR = tex_files
OPTIONS = -pdf -output-directory=$(DIR)
PDF_V = evince			#open, okular, skim, adobe...

basic: $(FILE).tex
	pdflatex $(OPTIONS) $<

auto: $(FILE).tex
	latexmk $(OPTIONS) $<

view: $(DIR)/$(FILE).pdf
	$(PDF_V) $< &
