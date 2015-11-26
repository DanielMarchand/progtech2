# First level headers apparently not shown

[comment]: <> ()   bla bla
\author
Year      | Name
:-------: | -------------
2015 | Programming Techniques for Scientific Simulations II, ETH Zürich
\copyright Licensed under the Apache License. See COPYING for details.

The aim of this framework is to simulate the Penna model 
(http://www.ncbi.nlm.nih.gov/pmc/articles/PMC2789689/)
and further introduce multiple species and interactions between them 
(as in Lotka-Volterra). We refer to this joint model as \b PennaLV.

This framework contains two libraries:
* a collection of animals (\ref zoo)
* a framework to simulate a collection of animals and their interaction (\ref sim)

Simulating PennaLV with only one animal species (i.e. sheep), we see that the mutation rate
influences the stable population count. The following plot shows the 
sheep population over 300 generations with mutation rate 3. The stable population 
(the decay is due to the carry capacity) is around 150 sheep.
![penna_low](../include/penna low mutation.png?raw=true)

If we increase the mutation rate, the stable population count drops to 100.
![penna_high](../include/penna high mutation.png?raw=true)

If we remove mutations (mutation rate 0) and add another species (i.e. bear) that interacts with
the sheep in a way, we can see the typical Lotka-Volterra oscillations.
![lotka_volterra](../include/lotka-volterra.png?raw=true)

If the two models are combined, we see both effects.
![pennaLV](../include/pennaLV.png?raw=true)



