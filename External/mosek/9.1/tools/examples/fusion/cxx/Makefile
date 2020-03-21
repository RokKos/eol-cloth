
#
# Compile and run MOSEK examples
#

CC=cl.exe
CCFLAGS=/EHsc
IPATHS=/I..\..\..\platform\win64x86\h 
LPATHS=/LIBPATH:..\..\..\platform\win64x86\bin
HERE=$(MAKEDIR)

fusion: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib

TrafficNetworkModel.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib TrafficNetworkModel.cc
	$(CC) $(CCFLAGS) $(IPATHS) TrafficNetworkModel.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

alan.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib alan.cc
	$(CC) $(CCFLAGS) $(IPATHS) alan.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

baker.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib baker.cc
	$(CC) $(CCFLAGS) $(IPATHS) baker.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

breaksolver.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib breaksolver.cc
	$(CC) $(CCFLAGS) $(IPATHS) breaksolver.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

callback.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib callback.cc
	$(CC) $(CCFLAGS) $(IPATHS) callback.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

cqo1.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib cqo1.cc
	$(CC) $(CCFLAGS) $(IPATHS) cqo1.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

ceo1.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib ceo1.cc
	$(CC) $(CCFLAGS) $(IPATHS) ceo1.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

pow1.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib pow1.cc
	$(CC) $(CCFLAGS) $(IPATHS) pow1.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

diet.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib diet.cc
	$(CC) $(CCFLAGS) $(IPATHS) diet.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

duality.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib duality.cc
	$(CC) $(CCFLAGS) $(IPATHS) duality.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

facility_location.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib facility_location.cc
	$(CC) $(CCFLAGS) $(IPATHS) facility_location.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

lo1.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib lo1.cc
	$(CC) $(CCFLAGS) $(IPATHS) lo1.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

gp1.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib gp1.cc
	$(CC) $(CCFLAGS) $(IPATHS) gp1.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

lownerjohn_ellipsoid.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib lownerjohn_ellipsoid.cc
	$(CC) $(CCFLAGS) $(IPATHS) lownerjohn_ellipsoid.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

lpt.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib lpt.cc
	$(CC) $(CCFLAGS) $(IPATHS) lpt.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

logistic.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib logistic.cc
	$(CC) $(CCFLAGS) $(IPATHS) logistic.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

milo1.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib milo1.cc
	$(CC) $(CCFLAGS) $(IPATHS) milo1.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

mioinitsol.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib mioinitsol.cc
	$(CC) $(CCFLAGS) $(IPATHS) mioinitsol.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

mico1.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib mico1.cc
	$(CC) $(CCFLAGS) $(IPATHS) mico1.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

modelLib.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib modelLib.cc
	$(CC) $(CCFLAGS) $(IPATHS) modelLib.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

nearestcorr.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib nearestcorr.cc
	$(CC) $(CCFLAGS) $(IPATHS) nearestcorr.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

opt_server_sync.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib opt_server_sync.cc
	$(CC) $(CCFLAGS) $(IPATHS) opt_server_sync.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

parameters.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib parameters.cc
	$(CC) $(CCFLAGS) $(IPATHS) parameters.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

portfolio_1_basic.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib portfolio_1_basic.cc
	$(CC) $(CCFLAGS) $(IPATHS) portfolio_1_basic.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

portfolio_2_frontier.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib portfolio_2_frontier.cc
	$(CC) $(CCFLAGS) $(IPATHS) portfolio_2_frontier.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

portfolio_3_impact.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib portfolio_3_impact.cc
	$(CC) $(CCFLAGS) $(IPATHS) portfolio_3_impact.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

portfolio_4_transcost.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib portfolio_4_transcost.cc
	$(CC) $(CCFLAGS) $(IPATHS) portfolio_4_transcost.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

portfolio_5_card.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib portfolio_5_card.cc
	$(CC) $(CCFLAGS) $(IPATHS) portfolio_5_card.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

primal_svm.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib primal_svm.cc
	$(CC) $(CCFLAGS) $(IPATHS) primal_svm.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

reoptimization.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib reoptimization.cc
	$(CC) $(CCFLAGS) $(IPATHS) reoptimization.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

response.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib response.cc
	$(CC) $(CCFLAGS) $(IPATHS) response.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

qcqp_sdo_relaxation.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib qcqp_sdo_relaxation.cc
	$(CC) $(CCFLAGS) $(IPATHS) qcqp_sdo_relaxation.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

sdo1.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib sdo1.cc
	$(CC) $(CCFLAGS) $(IPATHS) sdo1.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

sdo2.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib sdo2.cc
	$(CC) $(CCFLAGS) $(IPATHS) sdo2.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

sdo3.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib sdo3.cc
	$(CC) $(CCFLAGS) $(IPATHS) sdo3.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

sospoly.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib sospoly.cc
	$(CC) $(CCFLAGS) $(IPATHS) sospoly.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

sudoku.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib sudoku.cc
	$(CC) $(CCFLAGS) $(IPATHS) sudoku.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

total_variation.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib total_variation.cc
	$(CC) $(CCFLAGS) $(IPATHS) total_variation.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

tsp.exe: ..\..\..\platform\win64x86\bin\fusion64_9_1.lib tsp.cc
	$(CC) $(CCFLAGS) $(IPATHS) tsp.cc /link $(LPATHS) fusion64_9_1.lib mosek64_9_1.lib

all: TrafficNetworkModel.exe alan.exe baker.exe breaksolver.exe callback.exe cqo1.exe ceo1.exe pow1.exe diet.exe duality.exe facility_location.exe lo1.exe gp1.exe lownerjohn_ellipsoid.exe lpt.exe logistic.exe milo1.exe mioinitsol.exe mico1.exe modelLib.exe nearestcorr.exe opt_server_sync.exe parameters.exe portfolio_1_basic.exe portfolio_2_frontier.exe portfolio_3_impact.exe portfolio_4_transcost.exe portfolio_5_card.exe primal_svm.exe reoptimization.exe response.exe qcqp_sdo_relaxation.exe sdo1.exe sdo2.exe sdo3.exe sospoly.exe sudoku.exe total_variation.exe tsp.exe

clean:
	del TrafficNetworkModel.exe alan.exe baker.exe breaksolver.exe callback.exe cqo1.exe ceo1.exe pow1.exe diet.exe duality.exe facility_location.exe lo1.exe gp1.exe lownerjohn_ellipsoid.exe lpt.exe logistic.exe milo1.exe mioinitsol.exe mico1.exe modelLib.exe nearestcorr.exe opt_server_sync.exe parameters.exe portfolio_1_basic.exe portfolio_2_frontier.exe portfolio_3_impact.exe portfolio_4_transcost.exe portfolio_5_card.exe primal_svm.exe reoptimization.exe response.exe qcqp_sdo_relaxation.exe sdo1.exe sdo2.exe sdo3.exe sospoly.exe sudoku.exe total_variation.exe tsp.exe

test: TrafficNetworkModel.exe alan.exe baker.exe breaksolver.exe callback.exe cqo1.exe ceo1.exe pow1.exe diet.exe duality.exe facility_location.exe lo1.exe gp1.exe lownerjohn_ellipsoid.exe lpt.exe logistic.exe milo1.exe mioinitsol.exe mico1.exe modelLib.exe nearestcorr.exe opt_server_sync.exe parameters.exe portfolio_1_basic.exe portfolio_2_frontier.exe portfolio_3_impact.exe portfolio_4_transcost.exe portfolio_5_card.exe primal_svm.exe reoptimization.exe response.exe qcqp_sdo_relaxation.exe sdo1.exe sdo2.exe sdo3.exe sospoly.exe sudoku.exe total_variation.exe tsp.exe
	set PATH=..\..\..\platform\win64x86\bin;%PATH%
	TrafficNetworkModel.exe
	alan.exe
	baker.exe
	breaksolver.exe
	callback.exe
	cqo1.exe
	ceo1.exe
	pow1.exe
	diet.exe
	duality.exe
	facility_location.exe
	lo1.exe
	gp1.exe
	lownerjohn_ellipsoid.exe
	lpt.exe
	logistic.exe
	milo1.exe
	mioinitsol.exe
	mico1.exe
	modelLib.exe
	nearestcorr.exe
	opt_server_sync.exe
	parameters.exe
	portfolio_1_basic.exe
	portfolio_2_frontier.exe
	portfolio_3_impact.exe
	portfolio_4_transcost.exe
	portfolio_5_card.exe
	primal_svm.exe
	reoptimization.exe
	response.exe
	qcqp_sdo_relaxation.exe
	sdo1.exe
	sdo2.exe
	sdo3.exe
	sospoly.exe
	sudoku.exe
	total_variation.exe
	tsp.exe
