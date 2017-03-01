COMPILER = pdflatex
TEMP_FILES = $(wildcard *.aux) $(wildcard *.idx) $(wildcard *.log) $(wildcard *.toc)

all: main_en.pdf main_fr.pdf

%.pdf: %.tex
	$COMPILER $<

clean:
	rm -f $(TEMP_FILES)

rclean: clean
	rm -f main_en.pdf main_fr.pdf
