cd /usr/local/share/docbook-xsl-1.64.1/html
java -classpath /usr/local/share/saxon6_5_3/saxon.jar com.icl.saxon.StyleSheet /Users/jhainley/work/picprep/docs/docbook/picprep-usermanual-osx.dbk.xml docbook.xsl > /Users/jhainley/work/picprep/docs/picprep-usermanual-osx.html
cd /Users/jhainley/work/picprep/docs
chown jhainley:admin picprep-usermanual-osx.html
