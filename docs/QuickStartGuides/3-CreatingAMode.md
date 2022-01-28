# Creating A New Mode

*Note: this guide is only for versions greater than 0.1. If you'd like to check out this functionality sooner, it is on the `refactor` branch.*

Once you have familiarized yourself with Symbulation and its default mode, you might be interested in designing
your own experiment, adding functionality to the codebase, and collecting data. The existing modes include
default (Host and Symbiont), efficient (Efficient Host and Efficient Symbiont), lysis (Bacterium and Phage),
and public goods game or PGG (PGG Host and PGG Symbiont). There are several steps to creating your own world,
including following conventions for file structure, adding your own organisms, designing tests, adding a 
WorldSetup file, adding targets to the makefile, and more. 
