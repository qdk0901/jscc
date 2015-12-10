CC = gcc

XX = g++

CFLAGS = -Wall -O -Wno-attributes
CFLAGS += -DEVHTP_SYS_ARCH=64 -DJERRY_ENABLE_SNAPSHOT=1
CFLAGS += -DJERRY_BRANCH_NAME=\"refs/heads/master\" -DJERRY_BUILD_DATE=\"27/11/2015\" -DJERRY_COMMIT_HASH=\"f20db76dfb59e557b0a06f2dc4db05fc2b8ba639\"
CFLAGS += -DCONFIG_ECMA_NUMBER_TYPE=2
CFLAGS += -Ijerryscript/jerry-core/ecma/base/ \
		-Ijerryscript/jerry-core/ecma/builtin-objects/ \
		-Ijerryscript/jerry-core/ecma/operations/ \
		-Ijerryscript/jerry-core/ \
		-Ijerryscript/jerry-core/jrt/ \
		-Ijerryscript/jerry-core/lit/ \
		-Ijerryscript/jerry-core/mem/ \
		-Ijerryscript/jerry-core/parser/js/collections/ \
		-Ijerryscript/jerry-core/parser/js/ \
		-Ijerryscript/jerry-core/parser/regexp/ \
		-Ijerryscript/jerry-core/rcs/ \
		-Ijerryscript/jerry-core/vm/ \
		-Ijerryscript/third-party/fdlibm/include

#CFLAGS += -DJERRY_NDEBUG=1 -DJERRY_DISABLE_HEAVY_DEBUG=1

SOURCES = \
	jerryscript/jerry-core/ecma/base/ecma-alloc.cpp \
	jerryscript/jerry-core/ecma/base/ecma-gc.cpp \
	jerryscript/jerry-core/ecma/base/ecma-helpers-conversion.cpp \
	jerryscript/jerry-core/ecma/base/ecma-helpers-external-pointers.cpp \
	jerryscript/jerry-core/ecma/base/ecma-helpers-number.cpp \
	jerryscript/jerry-core/ecma/base/ecma-helpers-string.cpp \
	jerryscript/jerry-core/ecma/base/ecma-helpers-value.cpp \
	jerryscript/jerry-core/ecma/base/ecma-helpers-values-collection.cpp \
	jerryscript/jerry-core/ecma/base/ecma-helpers.cpp \
	jerryscript/jerry-core/ecma/base/ecma-init-finalize.cpp \
	jerryscript/jerry-core/ecma/base/ecma-lcache.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-array-prototype.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-array.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-boolean-prototype.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-boolean.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-compact-profile-error.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-date-prototype.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-date.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-error-prototype.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-error.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-evalerror-prototype.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-evalerror.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-function-prototype.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-function.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-global.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-helpers-date.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-helpers-json.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-helpers.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-json.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-math.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-number-prototype.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-number.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-object-prototype.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-object.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-rangeerror-prototype.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-rangeerror.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-referenceerror-prototype.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-referenceerror.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-regexp-prototype.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-regexp.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-string-prototype.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-string.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-syntaxerror-prototype.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-syntaxerror.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-type-error-thrower.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-typeerror-prototype.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-typeerror.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-urierror-prototype.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-urierror.cpp \
	jerryscript/jerry-core/ecma/builtin-objects/ecma-builtins.cpp \
	jerryscript/jerry-core/ecma/operations/ecma-array-object.cpp \
	jerryscript/jerry-core/ecma/operations/ecma-boolean-object.cpp \
	jerryscript/jerry-core/ecma/operations/ecma-comparison.cpp \
	jerryscript/jerry-core/ecma/operations/ecma-conversion.cpp \
	jerryscript/jerry-core/ecma/operations/ecma-eval.cpp \
	jerryscript/jerry-core/ecma/operations/ecma-exceptions.cpp \
	jerryscript/jerry-core/ecma/operations/ecma-function-object.cpp \
	jerryscript/jerry-core/ecma/operations/ecma-get-put-value.cpp \
	jerryscript/jerry-core/ecma/operations/ecma-lex-env.cpp \
	jerryscript/jerry-core/ecma/operations/ecma-number-arithmetic.cpp \
	jerryscript/jerry-core/ecma/operations/ecma-number-object.cpp \
	jerryscript/jerry-core/ecma/operations/ecma-objects-arguments.cpp \
	jerryscript/jerry-core/ecma/operations/ecma-objects-general.cpp \
	jerryscript/jerry-core/ecma/operations/ecma-objects.cpp \
	jerryscript/jerry-core/ecma/operations/ecma-reference.cpp \
	jerryscript/jerry-core/ecma/operations/ecma-regexp-object.cpp \
	jerryscript/jerry-core/ecma/operations/ecma-string-object.cpp \
	jerryscript/jerry-core/jerry.cpp \
	jerryscript/jerry-core/jrt/jrt-bit-fields.cpp \
	jerryscript/jerry-core/jrt/jrt-fatals.cpp \
	jerryscript/jerry-core/lit/lit-char-helpers.cpp \
	jerryscript/jerry-core/lit/lit-literal-storage.cpp \
	jerryscript/jerry-core/lit/lit-literal.cpp \
	jerryscript/jerry-core/lit/lit-magic-strings.cpp \
	jerryscript/jerry-core/lit/lit-strings.cpp \
	jerryscript/jerry-core/mem/mem-allocator.cpp \
	jerryscript/jerry-core/mem/mem-heap.cpp \
	jerryscript/jerry-core/mem/mem-poolman.cpp \
	jerryscript/jerry-core/parser/js/collections/array-list.cpp \
	jerryscript/jerry-core/parser/js/collections/hash-table.cpp \
	jerryscript/jerry-core/parser/js/collections/linked-list.cpp \
	jerryscript/jerry-core/parser/js/collections/lit-id-hash-table.cpp \
	jerryscript/jerry-core/parser/js/jsp-early-error.cpp \
	jerryscript/jerry-core/parser/js/jsp-label.cpp \
	jerryscript/jerry-core/parser/js/jsp-mm.cpp \
	jerryscript/jerry-core/parser/js/lexer.cpp \
	jerryscript/jerry-core/parser/js/opcodes-dumper.cpp \
	jerryscript/jerry-core/parser/js/parser.cpp \
	jerryscript/jerry-core/parser/js/scopes-tree.cpp \
	jerryscript/jerry-core/parser/js/serializer.cpp \
	jerryscript/jerry-core/parser/regexp/re-compiler.cpp \
	jerryscript/jerry-core/parser/regexp/re-parser.cpp \
	jerryscript/jerry-core/rcs/rcs-chunked-list.cpp \
	jerryscript/jerry-core/rcs/rcs-recordset.cpp \
	jerryscript/jerry-core/vm/opcodes-agnostic.cpp \
	jerryscript/jerry-core/vm/opcodes-ecma-arithmetics.cpp \
	jerryscript/jerry-core/vm/opcodes-ecma-bitwise.cpp \
	jerryscript/jerry-core/vm/opcodes-ecma-equality.cpp \
	jerryscript/jerry-core/vm/opcodes-ecma-relational.cpp \
	jerryscript/jerry-core/vm/opcodes-ecma-try-catch-finally.cpp \
	jerryscript/jerry-core/vm/opcodes-for-in.cpp \
	jerryscript/jerry-core/vm/opcodes-helpers-variables.cpp \
	jerryscript/jerry-core/vm/opcodes-varg.cpp \
	jerryscript/jerry-core/vm/opcodes.cpp \
	jerryscript/jerry-core/vm/pretty-printer.cpp \
	jerryscript/jerry-core/vm/vm-stack.cpp \
	jerryscript/jerry-core/vm/vm.cpp \
	jerryscript/third-party/fdlibm/e_acos.c \
	jerryscript/third-party/fdlibm/e_asin.c \
	jerryscript/third-party/fdlibm/e_atan2.c \
	jerryscript/third-party/fdlibm/e_exp.c \
	jerryscript/third-party/fdlibm/e_fmod.c \
	jerryscript/third-party/fdlibm/e_log.c \
	jerryscript/third-party/fdlibm/e_pow.c \
	jerryscript/third-party/fdlibm/e_rem_pio2.c \
	jerryscript/third-party/fdlibm/e_sqrt.c \
	jerryscript/third-party/fdlibm/k_cos.c \
	jerryscript/third-party/fdlibm/k_rem_pio2.c \
	jerryscript/third-party/fdlibm/k_sin.c \
	jerryscript/third-party/fdlibm/k_standard.c \
	jerryscript/third-party/fdlibm/k_tan.c \
	jerryscript/third-party/fdlibm/s_atan.c \
	jerryscript/third-party/fdlibm/s_ceil.c \
	jerryscript/third-party/fdlibm/s_copysign.c \
	jerryscript/third-party/fdlibm/s_cos.c \
	jerryscript/third-party/fdlibm/s_fabs.c \
	jerryscript/third-party/fdlibm/s_finite.c \
	jerryscript/third-party/fdlibm/s_floor.c \
	jerryscript/third-party/fdlibm/s_isnan.c \
	jerryscript/third-party/fdlibm/s_lib_version.c \
	jerryscript/third-party/fdlibm/s_rint.c \
	jerryscript/third-party/fdlibm/s_scalbn.c \
	jerryscript/third-party/fdlibm/s_sin.c \
	jerryscript/third-party/fdlibm/s_tan.c \
	jerryscript/third-party/fdlibm/s_tanh.c \
	jerryscript/third-party/fdlibm/w_acos.c \
	jerryscript/third-party/fdlibm/w_asin.c \
	jerryscript/third-party/fdlibm/w_atan2.c \
	jerryscript/third-party/fdlibm/w_exp.c \
	jerryscript/third-party/fdlibm/w_fmod.c \
	jerryscript/third-party/fdlibm/w_log.c \
	jerryscript/third-party/fdlibm/w_pow.c \
	jerryscript/third-party/fdlibm/w_sqrt.c \
	libev/ev.c \
	http-parser/http_parser.c \
	JsObject.cpp \
	JsUart.cpp \
	JsHttp.cpp \
	jscc.cpp

TARGET = jscc
	
%.o: %.c
	 $(CC) $(CFLAGS) -c $< -o $@

%.o:%.cpp
	 $(XX) $(CFLAGS) -std=c++11 -c $< -o $@
	
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))


$(TARGET) : $(OBJS)
	 $(XX) $(OBJS) -o $(TARGET)
	 chmod a+x $(TARGET)
	 
clean:
	find -name "*.o" -exec rm -f {} \; 
	