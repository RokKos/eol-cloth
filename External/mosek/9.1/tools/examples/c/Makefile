
#
# Compile and run MOSEK examples
#

CC=cl.exe
IPATHS=/I..\..\platform\win64x86\h
LPATHS=/LIBPATH:..\..\platform\win64x86\bin

blas_lapack.exe: blas_lapack.c
	$(CC) $(IPATHS) blas_lapack.c /link mosek64_9_1.lib $(LPATHS) /out:blas_lapack.exe

callback.exe: callback.c
	$(CC) $(IPATHS) callback.c /link mosek64_9_1.lib $(LPATHS) /out:callback.exe

portfolio_1_basic.exe: portfolio_1_basic.c
	$(CC) $(IPATHS) portfolio_1_basic.c /link mosek64_9_1.lib $(LPATHS) /out:portfolio_1_basic.exe

portfolio_2_frontier.exe: portfolio_2_frontier.c
	$(CC) $(IPATHS) portfolio_2_frontier.c /link mosek64_9_1.lib $(LPATHS) /out:portfolio_2_frontier.exe

portfolio_3_impact.exe: portfolio_3_impact.c
	$(CC) $(IPATHS) portfolio_3_impact.c /link mosek64_9_1.lib $(LPATHS) /out:portfolio_3_impact.exe

portfolio_4_transcost.exe: portfolio_4_transcost.c
	$(CC) $(IPATHS) portfolio_4_transcost.c /link mosek64_9_1.lib $(LPATHS) /out:portfolio_4_transcost.exe

portfolio_5_card.exe: portfolio_5_card.c
	$(CC) $(IPATHS) portfolio_5_card.c /link mosek64_9_1.lib $(LPATHS) /out:portfolio_5_card.exe

cqo1.exe: cqo1.c
	$(CC) $(IPATHS) cqo1.c /link mosek64_9_1.lib $(LPATHS) /out:cqo1.exe

ceo1.exe: ceo1.c
	$(CC) $(IPATHS) ceo1.c /link mosek64_9_1.lib $(LPATHS) /out:ceo1.exe

pow1.exe: pow1.c
	$(CC) $(IPATHS) pow1.c /link mosek64_9_1.lib $(LPATHS) /out:pow1.exe

errorreporting.exe: errorreporting.c
	$(CC) $(IPATHS) errorreporting.c /link mosek64_9_1.lib $(LPATHS) /out:errorreporting.exe

feasrepairex1.exe: feasrepairex1.c
	$(CC) $(IPATHS) feasrepairex1.c /link mosek64_9_1.lib $(LPATHS) /out:feasrepairex1.exe

lo1.exe: lo1.c
	$(CC) $(IPATHS) lo1.c /link mosek64_9_1.lib $(LPATHS) /out:lo1.exe

lo2.exe: lo2.c
	$(CC) $(IPATHS) lo2.c /link mosek64_9_1.lib $(LPATHS) /out:lo2.exe

logistic.exe: logistic.c
	$(CC) $(IPATHS) logistic.c /link mosek64_9_1.lib $(LPATHS) /out:logistic.exe

gp1.exe: gp1.c
	$(CC) $(IPATHS) gp1.c /link mosek64_9_1.lib $(LPATHS) /out:gp1.exe

milo1.exe: milo1.c
	$(CC) $(IPATHS) milo1.c /link mosek64_9_1.lib $(LPATHS) /out:milo1.exe

mioinitsol.exe: mioinitsol.c
	$(CC) $(IPATHS) mioinitsol.c /link mosek64_9_1.lib $(LPATHS) /out:mioinitsol.exe

mico1.exe: mico1.c
	$(CC) $(IPATHS) mico1.c /link mosek64_9_1.lib $(LPATHS) /out:mico1.exe

modelLib.exe: modelLib.c
	$(CC) $(IPATHS) modelLib.c /link mosek64_9_1.lib $(LPATHS) /out:modelLib.exe

opt_server_async.exe: opt_server_async.c
	$(CC) $(IPATHS) opt_server_async.c /link mosek64_9_1.lib $(LPATHS) /out:opt_server_async.exe

opt_server_sync.exe: opt_server_sync.c
	$(CC) $(IPATHS) opt_server_sync.c /link mosek64_9_1.lib $(LPATHS) /out:opt_server_sync.exe

parameters.exe: parameters.c
	$(CC) $(IPATHS) parameters.c /link mosek64_9_1.lib $(LPATHS) /out:parameters.exe

reoptimization.exe: reoptimization.c
	$(CC) $(IPATHS) reoptimization.c /link mosek64_9_1.lib $(LPATHS) /out:reoptimization.exe

qcqo1.exe: qcqo1.c
	$(CC) $(IPATHS) qcqo1.c /link mosek64_9_1.lib $(LPATHS) /out:qcqo1.exe

qo1.exe: qo1.c
	$(CC) $(IPATHS) qo1.c /link mosek64_9_1.lib $(LPATHS) /out:qo1.exe

response.exe: response.c
	$(CC) $(IPATHS) response.c /link mosek64_9_1.lib $(LPATHS) /out:response.exe

sdo1.exe: sdo1.c
	$(CC) $(IPATHS) sdo1.c /link mosek64_9_1.lib $(LPATHS) /out:sdo1.exe

sdo2.exe: sdo2.c
	$(CC) $(IPATHS) sdo2.c /link mosek64_9_1.lib $(LPATHS) /out:sdo2.exe

sensitivity.exe: sensitivity.c
	$(CC) $(IPATHS) sensitivity.c /link mosek64_9_1.lib $(LPATHS) /out:sensitivity.exe

simple.exe: simple.c
	$(CC) $(IPATHS) simple.c /link mosek64_9_1.lib $(LPATHS) /out:simple.exe

solutionquality.exe: solutionquality.c
	$(CC) $(IPATHS) solutionquality.c /link mosek64_9_1.lib $(LPATHS) /out:solutionquality.exe

solvebasis.exe: solvebasis.c
	$(CC) $(IPATHS) solvebasis.c /link mosek64_9_1.lib $(LPATHS) /out:solvebasis.exe

solvelinear.exe: solvelinear.c
	$(CC) $(IPATHS) solvelinear.c /link mosek64_9_1.lib $(LPATHS) /out:solvelinear.exe

sparsecholesky.exe: sparsecholesky.c
	$(CC) $(IPATHS) sparsecholesky.c /link mosek64_9_1.lib $(LPATHS) /out:sparsecholesky.exe

unicode.exe: unicode.c
	$(CC) $(IPATHS) unicode.c /link mosek64_9_1.lib $(LPATHS) /out:unicode.exe

all: blas_lapack.exe callback.exe portfolio_1_basic.exe portfolio_2_frontier.exe portfolio_3_impact.exe portfolio_4_transcost.exe portfolio_5_card.exe cqo1.exe ceo1.exe pow1.exe errorreporting.exe feasrepairex1.exe lo1.exe lo2.exe logistic.exe gp1.exe milo1.exe mioinitsol.exe mico1.exe modelLib.exe opt_server_async.exe opt_server_sync.exe parameters.exe reoptimization.exe qcqo1.exe qo1.exe response.exe sdo1.exe sdo2.exe sensitivity.exe simple.exe solutionquality.exe solvebasis.exe solvelinear.exe sparsecholesky.exe unicode.exe

clean:
	del blas_lapack.exe callback.exe portfolio_1_basic.exe portfolio_2_frontier.exe portfolio_3_impact.exe portfolio_4_transcost.exe portfolio_5_card.exe cqo1.exe ceo1.exe pow1.exe errorreporting.exe feasrepairex1.exe lo1.exe lo2.exe logistic.exe gp1.exe milo1.exe mioinitsol.exe mico1.exe modelLib.exe opt_server_async.exe opt_server_sync.exe parameters.exe reoptimization.exe qcqo1.exe qo1.exe response.exe sdo1.exe sdo2.exe sensitivity.exe simple.exe solutionquality.exe solvebasis.exe solvelinear.exe sparsecholesky.exe unicode.exe

test: blas_lapack.exe callback.exe portfolio_1_basic.exe portfolio_2_frontier.exe portfolio_3_impact.exe portfolio_4_transcost.exe portfolio_5_card.exe cqo1.exe ceo1.exe pow1.exe errorreporting.exe feasrepairex1.exe lo1.exe lo2.exe logistic.exe gp1.exe milo1.exe mioinitsol.exe mico1.exe modelLib.exe opt_server_async.exe opt_server_sync.exe parameters.exe reoptimization.exe qcqo1.exe qo1.exe response.exe sdo1.exe sdo2.exe sensitivity.exe simple.exe solutionquality.exe solvebasis.exe solvelinear.exe sparsecholesky.exe unicode.exe
	set PATH=..\..\platform\win64x86\bin;%%PATH%%
	blas_lapack.exe
	callback.exe
	portfolio_1_basic.exe
	portfolio_2_frontier.exe
	portfolio_3_impact.exe
	portfolio_4_transcost.exe
	portfolio_5_card.exe
	cqo1.exe
	ceo1.exe
	pow1.exe
	errorreporting.exe
	feasrepairex1.exe
	lo1.exe
	lo2.exe
	logistic.exe
	gp1.exe
	milo1.exe
	mioinitsol.exe
	mico1.exe
	modelLib.exe
	opt_server_async.exe
	opt_server_sync.exe
	parameters.exe
	reoptimization.exe
	qcqo1.exe
	qo1.exe
	response.exe
	sdo1.exe
	sdo2.exe
	sensitivity.exe
	simple.exe
	solutionquality.exe
	solvebasis.exe
	solvelinear.exe
	sparsecholesky.exe
	unicode.exe
