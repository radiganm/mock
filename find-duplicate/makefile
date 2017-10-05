#!/usr/bin/make
## makefile
## Mac Radigan

.PHONY: pandoc view clean clobber build packages-apt run

.DEFAULT_GOAL := default

target = find-duplicate
output = .

default: doc build

build:
	g++ -o $(target) $(target).cxx

run:
	./$(target)

doc: pandoc

pandoc:
	pandoc $(output)/$(target).md           \
	     --wrap=preserve                    \
	     --template=../include/template.tex \
	     -f markdown                        \
	     -F pandoc-minted                   \
	     -t latex                           \
	     -o $(target).tex
	pdflatex --shell-escape $(target).tex

view:
	@zathura -x -a $(target).pdf 1>/dev/null 2>/dev/null

clobber: clean
	-rm -f $(target).pdf

clean:
	-rm -f $(target).tex
	-rm -f $(target).aux
	-rm -f $(target).log
	-rm -f $(target).out
	-rm -f $(target).aux
	-rm -f ./$(target)


packages-apt:
	apt-get install -y build-essential
	apt-get install -y radare2

## *EOF*
