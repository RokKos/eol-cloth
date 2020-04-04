#include "Scene.h"
#include "Cloth.h"
#include "Obstacles.h"
#include "Shape.h"
#include "Preprocessor.h"
#include "Collisions.h"
#include "Constraints.h"
#include "GeneralizedSolver.h"
#include "matlabOutputs.h"

#include "external\ArcSim\dynamicremesh.hpp"

#ifdef EOLC_ONLINE
#include "online\MatrixStack.h"
#include "online\Program.h"
#endif // EOLC_ONLINE

#include "Core/Log.h"

using namespace Eigen;

Scene::Scene() : 
	t(0.0),
	h(0.005),
	grav(Vector3d(0.0,0.0,-9.8)),
	part(0)
{
	cloth = std::make_shared<Cloth>();
	obs = std::make_shared<Obstacles>();
	GS = std::make_shared<GeneralizedSolver>();
}

void Scene::load(const std::string &RESOURCE_DIR)
{
	obs->load(RESOURCE_DIR);
}

void Scene::init(const bool& online, const bool& exportObjs, const std::string& OUTPUT_DIR)
{
#ifdef EOLC_ONLINE
	if (online) {
		cloth->init();
		obs->init();
	}
#endif

	if (REMESHon) {
		dynamic_remesh(cloth->mesh);
		set_indices(cloth->mesh);
	}

	cloth->consts->init(obs);

	if (exportObjs) {
		brender = BrenderManager::getInstance();
		brender->setExportDir(OUTPUT_DIR);
		brender->add(cloth);
		obs->addExport(brender);
		brender->exportBrender(t);
	}
}

void printstate(Mesh& mesh)
{
	for (int n = 0; n < mesh.nodes.size(); n++) {
		if (mesh.nodes[n]->EoL) {
			LOG_TRACE(mesh.nodes[n]->EoL_state);
		}
	}
}

void Scene::step(const bool& online, const bool& exportObjs)
{
	LOG_TRACE("Sim time: '{0}'", t);

	if (part != 0) {
		LOG_WARN("Please finish the partial step before making a full step");
		return;
	}
	cloth->updateFix(t);
	if (EOLon) {
		cloth->updatePreviousMesh();
		CD(cloth->mesh, obs, cls);
		preprocess(cloth->mesh, cloth->boundaries, cls);
		//std::cout << "pre" << std::endl;
	}
	if (REMESHon) {
		dynamic_remesh(cloth->mesh);
		set_indices(cloth->mesh);
	}
	cloth->step(GS, obs, grav, h, REMESHon, online);
	obs->step(h);
	cls.clear();
	//mesh2m(cloth->mesh, "mesh.m", true);
	if (exportObjs) brender->exportBrender(t);
	//std::cout << "step" << std::endl;
	t += h;
}

void Scene::partialStep()
{
	if (part == 0) {
		cloth->updatePreviousMesh();
		cloth->updateFix(t);
		CD(cloth->mesh, obs, cls);
		LOG_INFO("CD");
	}
	else if (part >= 1 && part < 8) {
		preprocessPart(cloth->mesh, cloth->boundaries, cls, part);
		set_indices(cloth->mesh);
		cloth->updateBuffers();
		mesh2m(cloth->mesh, "mesh.m", true);
	}
	else if (part == 8) {
		dynamic_remesh(cloth->mesh);
		set_indices(cloth->mesh);
		cloth->updateBuffers();
	}
	else if (part == 9) {
		cloth->step(GS, obs, grav, h, REMESHon, true);
		obs->step(h);
		LOG_INFO("Finished step");
		cls.clear();
		part = -1;
	}
	part++;
}

#ifdef EOLC_ONLINE
void Scene::draw(std::shared_ptr<MatrixStack> MV, const std::shared_ptr<Program> p) const
{
	obs->draw(MV,p);

	glUniform3fv(p->getUniform("kdFront"), 1, Vector3f(1.0, 0.5, 0.5).data());
	glUniform3fv(p->getUniform("kdBack"), 1, Vector3f(1.0, 0.5, 0.5).data());
	cloth->draw(MV, p);
}

void Scene::drawSimple(std::shared_ptr<MatrixStack> MV, const std::shared_ptr<Program> p) const
{
	obs->drawSimple(MV, p);
	cloth->drawSimple(MV, p);
}
#endif // EOLC_ONLINE
