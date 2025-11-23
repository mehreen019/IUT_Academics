@echo off
echo Building LaTeX document with bibliography...

REM First pass - generate aux file
pdflatex labfinal.tex

REM Process bibliography
bibtex labfinal

REM Second pass - incorporate bibliography
pdflatex labfinal.tex

REM Third pass - resolve all references
pdflatex labfinal.tex

REM Clean up auxiliary files (optional)
REM del *.aux *.log *.out *.toc *.synctex.gz *.bbl *.blg 2>nul

echo Build complete! Output: labfinal.pdf