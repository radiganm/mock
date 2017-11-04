#!/usr/bin/make
## makefile
## Mac Radigan

.PHONY: init pandoc view clean clobber build packages-apt run dist

.DEFAULT_GOAL := default

target = sum-two-terms

date = $(shell date +%F)

distributable   = ./dist
include         = ./include
markdown        = ./markdown
output          = ./output
results         = ./results
source          = ./src
template        = ./template

default: doc build

doc: pandoc

build: init
	$(MAKE) -C $(source) $@

run: build
	$(MAKE) -C $(source) $@

dox: $(source)
	rm -rf $(output)
	env PYTHONPATH=../dox/library            \
	  python3 ../dox/dox.py                  \
	    -v -r                                \
	    -I $(markdown):$(source):$(results)  \
	    -t $(template)                       \
	    -o $(output)

pandoc: dox run
	pandoc $(output)/$(target).md            \
	     --wrap=preserve                     \
	     --template=$(markdown)/template.tex \
	     --filter pandoc-eqnos               \
	     -M cleveref=On                      \
	     -f markdown                         \
	     --highlight-style=tango             \
	     -t latex                            \
	     -o $(target).tex
	pdflatex --shell-escape $(target).tex

view:
	@zathura -x -a $(target).pdf 1>/dev/null 2>/dev/null

clobber: clean
	$(MAKE) -C $(source) $@
	-rm -Rf $(distributable)
	-rm -f $(target).pdf

clean:
	$(MAKE) -C $(source) $@
	-rm -f $(target).tex
	-rm -f $(target).aux
	-rm -f $(target).log
	-rm -f $(target).out
	-rm -f $(target).aux
	-rm -f ./$(target)

init:
	mkdir -p $(figures) $(results)

packages-apt:
	apt-get install -y build-essential
	apt-get install -y radare2

dist: doc
	rm -Rf $(distributable)
	mkdir -p $(distributable)/$(package)
	rsync -avhr $(target).pdf $(distributable)/$(package)
	rsync -avhr $(template)   $(distributable)/$(package)
	rsync -avhr $(include)    $(distributable)/$(package)
	rsync -avhr $(source)     $(distributable)/$(package)
	rsync -avhr makefile      $(distributable)/$(package)
	(cd $(distributable); zip -r $(package)_$(date).zip $(package) )
	(cd $(distributable); openssl sha1 $(package)_$(date).zip >$(package)_$(date).zip.sha1 )

## *EOF*
