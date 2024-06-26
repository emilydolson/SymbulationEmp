# ALIFE 2022 Symbulation Tutorial

We will be hosting a introduction to Symbulation tutorial at the [ALIFE 2022 conferece](https://2022.alife.org/)!

## Overview
Symbulation is an agent-based modeling platform that enables the study of symbiosis along the parasitism to mutualism spectrum and available at [https://github.com/anyaevostinar/SymbulationEmp](https://github.com/anyaevostinar/SymbulationEmp). It uses the Empirical platform and allows for a large amount of customization based on existing functionality, including allowing symbionts to live outside or inside of hosts, lysogenic and lytic life cycles, several different spatial structures, and enabling symbionts occupying the same host to engage in a public goods game. It also supports the creation of new modes and functionality for those with some C++ experience. There are 56 current configuration options, controlled by an easy-to-use configuration file and customizable data-tracking. It also includes a web-based graphical user interface that can be customized by those with C++ knowledge. Symbulation is already being used  to study how spatial structure and multi-infection interact with the evolution of mutualistic symbiosis, the evolution of lysogeny, and the de novo evolution of endosymbiosis. It has also been used in classroom settings with advanced undergraduate computer science students. 

This tutorial will guide new users in understanding the overall architecture of Symbulation, setting up a project (using our [Cookiecutter](https://github.com/anyaevostinar/SymbulationProjectTemplate) template) to conduct an experiment using existing configuration options,  customizing the browser-based graphical user interface, and creating new functionality for those comfortable with C++. The tutorial will build on the existing guides and documentation (available at [https://symbulation.readthedocs.io/en/latest/](https://symbulation.readthedocs.io/en/latest/)) and a page for the tutorial will be created there. Attendees will also be able to shape the future directions of Symbulation by discussing new desirable features and contributing their new functionality back to the codebase if they so wish. Attendees will leave the tutorial with the start of a new research project and, ideally, lots of new ideas and potential collaborations.

All material will be hosted here.

## Advanced Prep
You don't need to do anything in advance of the workshop to gain from the time.
However, if you want, there are some things that you could install ahead of time to speed things up:

* If you use a Windows system, we recommend that you install [Windows Subsystem for Linux](https://docs.microsoft.com/en-us/windows/wsl/) (Symbulation doesn't run on Windows unfortunately)
* [Check if you have `gcc` and if you don't, install it](https://symbulation.readthedocs.io/en/latest/QuickStartGuides/1-GettingRunning.html#install-native-c-compiler). **This install can take a while**, hence why it's good to do ahead of the workshop. (`clang` might work, but we'll assume that you are using `gcc` and won't be able to help with issues with `clang`.)
* [Install `cookiecutter` and pull down the Symbulation project template](https://symbulation.readthedocs.io/en/latest/QuickStartGuides/1-GettingRunning.html#using-cookiecutter) so that we can use it to set up the folder structure more easily. It will give an error at the end about not succeeding to push to GitHub; that's normal and nothing to worry about.
* [Install RStudio](https://docs.rstudio.com/) so that you can make plots of the data that you generate with our provided R scripts (if you don't have an R program already)
* If you don't want to/can't install things, you can do most things using [this Replit](https://replit.com/@anyaevostinar/Symbulation-Example), just not building the web version.

## Schedule

### Intro
(~20 Minutes)

* Get started downloading things (can be done in advance, see above for details)
    * If on Windows: [WSL](https://docs.microsoft.com/en-us/windows/wsl/)
    * [`gcc`](https://symbulation.readthedocs.io/en/latest/QuickStartGuides/1-GettingRunning.html#install-native-c-compiler)
    * [`cookiecutter`](https://symbulation.readthedocs.io/en/latest/QuickStartGuides/1-GettingRunning.html#using-cookiecutter)
* High-level of what Symbulation is and how it works

### Hands-on 1 
(~15 minutes)
* Work through [making a cookie cutter project and running it](https://symbulation.readthedocs.io/en/latest/QuickStartGuides/1-GettingRunning.html#using-cookiecutter)
* Work through [building the web version and running locally](https://symbulation.readthedocs.io/en/latest/QuickStartGuides/1-GettingRunning.html#install-web-gui)
* [Change some settings and get some data](https://symbulation.readthedocs.io/en/latest/QuickStartGuides/2-CollectingData.html); settings you could try changing:
    * VERTICAL_TRANSMISSION
    * GRID
    * FREE_LIVING_SYMS
    * MUTATION_SIZE

### Break 
(~10 minutes)

### Explaining Code Structure 
(~20 minutes)
* How all the classes work together
* Where the major functionality happens
* Where you might want to try out making changing

### Hands-on 2 
(~15 minutes)

* Work through [making a new configuration setting](https://symbulation.readthedocs.io/en/latest/QuickStartGuides/3-CreatingConfigSetting.html)
* Work through [making a new mode](https://symbulation.readthedocs.io/en/latest/QuickStartGuides/4-CreatingAMode.html)

### Wrap-up 
(~10 minutes)

* What do you think?
* What would you want to make Symbulation something you would use in your own research or teaching?

# ALIFE Talks Featuring Symbulation
Here are the talks at ALIFE 2022 that feature Symbulation! 
The links are in theory the Google Calendar invites, hopefully they work :).

* [Monday 15:30-15:50](https://calendar.google.com/calendar/u/0/r/eventedit?text=21.+Claire+Schregardus,+Michael+Wiser+and+Anya+VostinarDirty+Transmission+Hypothesis:+Increased+Mutations+During+Horizontal+Transmission+Can+Select+for+Increased+Levels+of+Mutualism+in+Endosymbionts&dates=20220718T133000Z/20220718T135000Z&details&location) 21. Claire Schregardus, Michael Wiser and Anya Vostinar Dirty Transmission Hypothesis: Increased Mutations During Horizontal Transmission Can Select for Increased Levels of Mutualism in Endosymbionts
* [Wednesday 15:20-15:40](https://calendar.google.com/calendar/u/0/r/eventedit?text=19.+Kiara+Johnson,+Piper+Welch,+Emily+Dolson+and+Anya+VostinarEndosymbiosis+or+Bust:+Influence+of+Ectosymbiosis+on+Evolution+of+Obligate+Endosymbiosis&dates=20220720T132000Z/20220720T134000Z&details&location) 19. Kiara Johnson, Piper Welch, Emily Dolson and Anya Vostinar Endosymbiosis or Bust: Influence of Ectosymbiosis on Evolution of Obligate Endosymbiosis
* [Wednesday 15:40-16:00](https://calendar.google.com/calendar/u/0/r/eventedit?text=20.+Alison+Cameron,+Seth+Dorchen,+Sarah+Doore+and+Anya+VostinarKeep+Your+Frenemies+Closer:+Bacteriophage+That+Benefit+Their+Hosts+Evolve+to+be+More+Temperate&dates=20220720T134000Z/20220720T140000Z&details&location) 20. Alison Cameron, Seth Dorchen, Sarah Doore and Anya Vostinar Keep Your Frenemies Closer: Bacteriophage That Benefit Their Hosts Evolve to be More Temperate
* [Thursday 15:00-15:20](https://calendar.google.com/calendar/u/0/r/eventedit?text=4.+Anya+Vostinar,+Katherine+Skocelas,+Alexander+Lalejini+and+Luis+ZamanSymbiosis+in+Digital+Evolution:+A+Review+and+Future+Directions&dates=20220721T130000Z/20220721T132000Z&details&location) 4. Anya Vostinar, Katherine Skocelas, Alexander Lalejini and Luis Zaman Symbiosis in Digital Evolution: A Review and Future Directions
* [Friday 15:00-15:20](https://calendar.google.com/calendar/u/0/r/eventedit?text=126.+Emily+Dolson,+Anya+Vostinar,+Shakeal+Hodge+and+Zhen+RenEvolutionary+stability+of+host-endosymbiont+mutualism+is+reduced+by+multi-infection&dates=20220722T130000Z/20220722T132000Z&details&location) 126. Emily Dolson, Anya Vostinar, Shakeal Hodge and Zhen Ren Evolutionary stability of host-endosymbiont mutualism is reduced by multi-infection

