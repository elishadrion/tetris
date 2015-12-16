FILE = srd
OPTIONS = -pdf
PDF_V = evince			#open, okular, skim, adobe...

auto: $(FILE).tex
	latexmk $(OPTIONS) $<

basic: $(FILE).tex
	pdflatex $(OPTIONS) $<

view: $(FILE).pdf
	$(PDF_V) $< &
