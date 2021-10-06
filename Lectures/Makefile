all: \
	00-sprawy-organizacyjne.pdf \
	01-intro-to-programming.pdf \
	01-intro-to-cxx.pdf \
	02-first-steps.pdf \
	03-loops.pdf \
	04-data-structures.pdf \
	05-threads.pdf \
	06-io.pdf

%.pdf: %.tex
	pdflatex -halt-on-error $^

%.png: %.dot
	dot -Tpng $^ > $@

again:
	touch *.tex
	make

watch:
	( find . -name '*.tex' -type f ; find . -name '*.bib' -type f) \
		| entr -pc make

clean-garbage:
	rm *.dvi || true
	rm *.log || true
	rm *.aux || true
	rm *.toc || true
	rm *.out || true
	rm *.nav || true
	rm *.snm || true
	rm *.vrb || true
	rm *.synctex.gz || true

clean-all: clean-garbage
	rm *.pdf || true

clean: clean-garbage
