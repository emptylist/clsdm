clsdm
=====

LSDM in C/C++, for cluster use

This project is largely defunct, as other tests and discussions suggest Locally Scaled Diffusion Maps is both extraordinarily expensive, computationally, and yields information of lower quality than directly building a Markov State Model.  Much of the value we could get from LSDM can really be encapsulated in the Distance Metric of the MSM builder, and thus it seems preferable to experiment with that directly.  Additionally, since MSMs are relatively cheap to build, we can potentially directly learn over iterated MSMs.

I'll leave this project in my github however, in the event that I have some time to dig into parallel C++ development, and need a decent project to work on, as LSDM could still be useful in other contexts.
