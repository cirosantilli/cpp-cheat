-include $(shell git rev-parse --show-toplevel)/Makefile_params
-include Makefile_params

OUTS = $(addsuffix $(OUT_EXT), $(OBJS_NOEXT))

all: mkdir $(OUTS)

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%$(CC_EXT) $(ALL_DEPEND)
	$(CC) $(CFLAGS) -o '$@' '$<' $(LIBS)

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%$(CXX_EXT) $(ALL_DEPEND)
	$(CXX) $(CXXFLAGS) -o '$@' '$<' $(LIBS)

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%$(FF_EXT) $(ALL_DEPEND)
	$(FF) $(FFLAGS) -o '$@' '$<' $(FFLIBS)

-include $(shell git rev-parse --show-toplevel)/Makefile_targets
-include Makefile_targets
