CC=pdflatex
CFLAGS=-shell-escape
CONFIG=settings/*.tex
OBJS=titlepage.tex schema.tex code_source.tex detail_code.tex
JOBNAME=compte_rendu

$(JOBNAME).pdf: $(JOBNAME).tex $(CONFIG) $(OBJS)
	$(CC) $(CFLAGS) $< ;

clean: 
	rm -rf _minted-$(JOBNAME) *~ $(JOBNAME).aux $(JOBNAME).toc $(JOBNAME).log $(JOBNAME).bbl $(JOBNAME).blg $(JOBNAME).gz $(JOBNAME).out $(JOBNAME)-*.asy $(JOBNAME)-*.pdf $(JOBNAME).pre $(JOBNAME).vrb $(JOBNAME).snm
