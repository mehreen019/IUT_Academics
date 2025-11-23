# Makefile for LaTeX document
TEX_FILE = labfinal.tex
PDF_FILE = labfinal.pdf

.PHONY: build clean

build:
	pdflatex $(TEX_FILE)
	pdflatex $(TEX_FILE)

clean:
	del /Q *.aux *.log *.out *.toc *.synctex.gz 2>nul || true

rebuild: clean build

help:
	@echo Available targets:
	@echo   build   - Build the PDF document
	@echo   clean   - Remove auxiliary files
	@echo   rebuild - Clean and build
	@echo   help    - Show this help message