INCLUDEPATH += ../lib/parser \
    ../lib/parser/sexp
win32:LIBS += ../lib/parser/sexp/sexpXP.a
else:LIBS += ../lib/parser/sexp/sexp.a

SOURCES += main.cpp\
  ../lib/optionsmanager/*.cpp\
  ../lib/parser/parser.cpp\
  ../lib/parser/structures.cpp\
  ../lib/*.cpp\
  ../piracy/*.cpp

MOC = moc

HEADERS += *.h\
  ../lib/optionsmanager/*.h\
  ../lib/renderer/*.h\
  ../lib/parser/*.h\
  ../piracy/*.h

CONFIG += debug
QT += opengl
