## Modifiable
##==============================================================================

# Nom du programme
PROG = prog

# Options Doxygen
PROJECTNAME       = "ProgParallele"
PROJECTBRIEF      = ""
OUTPUTLANGUAGE    = French

# Dossiers
SRCDIR 	= src/
BINDIR 	= bin/
DOCDIR 	= doc/
SAVEDIR = save/

# Utilisateur
FISRTNAME = Arthur
LASTNAME = Viens

# Options
OPT = -Wall -ansi -pedantic -l pthread -lm

# Compress extension
COMP = .tar.gz

## Section stable
##==============================================================================

CC = gcc
RM = rm -f
CP = cp -f
TAR = tar -zcvf


SRC = $(wildcard $(SRCDIR)*.c)
HEAD = $(wildcard $(SRCDIR)*.h)
OBJ = $(subst $(SRCDIR), $(BINDIR), $(SRC:.c=.o))

DIRS = $(SRCDIR) $(BINDIR) $(DOCDIR) $(SAVEDIR)

.PHONY : all clean save restore give doc help show

all : $(PROG) doc

# Règle pour générer les dossiers
#--------------------------------------------------------
$(DIRS) :
	mkdir -p $@


# Règle pour générer les fichiers objets (.o).
#--------------------------------------------------------
obj : $(OBJ) | $(BINDIR)

$(BINDIR)%.o : $(SRCDIR)%.c $(HEAD) | $(BINDIR)
	$(CC) $(OPT) -c $< -o $@

# Règle pour générer l'exécutable
#--------------------------------------------------------
$(PROG) : $(OBJ)
	$(CC) $^ -o $@ -lm
	@echo
	@echo Entrez ./$@ pour exécuter le programme.

# Règle pour effacer les fichiers temporaires
#--------------------------------------------------------
clean :
	find . -type f \( -name '*.o' -o -name '*\*\~' -o -name '*.bak' -o -name '*.old' -o -regex "^\#.*\#$$" \) -delete
	$(RM) $(PROG)

# Règle pour générer une sauvegarde
#--------------------------------------------------------
save : | $(SAVEDIR)
	$(CP) $(SRCDIR)* $(SAVEDIR)

# Règle pour restaurer une sauvegarde
#--------------------------------------------------------
restore : | $(SAVEDIR)
	$(CP) $(SAVEDIR)* $(SRCDIR)

# Règle pour générer une archive
#--------------------------------------------------------
give : readme
	$(TAR) $(LASTNAME)$(FISRTNAME)-$(PROG)$(COMP) $(SRCDIR) Makefile README.md


# Règle pour générer le README
#--------------------------------------------------------
readme :
	touch README.md


# Règle pour afficher l'aide
#--------------------------------------------------------
help :
	@echo 'Makefile pour des programmes C version 0.1'
	@echo 'Arthur Viens <abdulhamid@eisti.eu>'
	@echo
	@echo 'Utilisation: make [CIBLE]'
	@echo 'CIBLES:'
	@echo '  all       (=make) compile et édite les liens'
	@echo '  objs      Compile seulement (aucune édition des liens).'
	@echo "  clean     Nettoye les fichiers objets, temporaires et l'exécutable."
	@echo '  show      Affiche les variables.'
	@echo '  help      Affiche ce message.'
	@echo '  save      Crée une sauvegarde de src/ dans save/.'
	@echo '  restore   Restaure les fichiers du dossier save/.'
	@echo '  give      Génère une archive du projet/programme.'
	@echo '  doc       Génère une documentation du programme dans doc/.'
	@echo '  readme    Génère un fichier README.md.'

# Règle pour afficher les variables
#--------------------------------------------------------
show :
	@echo 'PROG        :' $(PROG)
	@echo 'SRCDIR      :' $(SRCDIR)
	@echo 'BINDIR      :' $(BINDIR)
	@echo 'SAVEDIR     :' $(SAVEDIR)
	@echo 'DOCDIR      :' $(DOCDIR)
	@echo 'HEAD        :' $(HEAD)
	@echo 'SRC         :' $(SRC)
	@echo 'OBJ         :' $(OBJ)
	@echo 'CC          :' $(CC)
	@echo 'OPT         :' $(OPT)
