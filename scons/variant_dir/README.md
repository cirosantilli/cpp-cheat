# VariantDir

Create multiple versions of the build depending on config files or command line parameters.

We could do something more advanced by:

- hashing all input arguments like `x` and name the output directory after them
- cat the input arguments to a file in that directory to enable identifying the directories

Can also be used for out-of-tree builds: https://stackoverflow.com/questions/3720142/how-to-force-scons-output-exe-obj-lib-dll-to-specific-build-directory
