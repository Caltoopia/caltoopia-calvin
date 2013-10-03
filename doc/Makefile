all: calvin.pdf

calvin.pdf: calvin.dvi
	dvipdf $^

calvin.dvi: calvin.tex
	latex $^ && latex $^

clean:
	rm -f *.aux *.dvi *.log *.pdf

.INTERMEDIATE: calvin.dvi