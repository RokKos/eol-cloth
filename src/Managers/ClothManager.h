#ifndef CLOTH_MANAGER_H
#define CLOTH_MANAGER_H

#include "../external/ArcSim/GeometryPrimitives/Mesh.h"
#include "../Cloth.h"

namespace EOL {

	class ClothManager 
	{
	public:
		static ClothManager& GetInstance()
		{
			static ClothManager instance; // Guaranteed to be destroyed.
										  // Instantiated on first use.
			return instance;
		}

		static std::shared_ptr<Cloth> GetClothParent(ARCSim::Mesh& mesh_child) { return GetInstance().GetClothParentImplementation(mesh_child); }
		static void AddCloth(std::shared_ptr<Cloth> cloth) { return GetInstance().AddClothImplementation(cloth); }

		ClothManager(ClothManager const&) = delete;
		void operator=(ClothManager const&) = delete;
		
	private:
		ClothManager() {};

		std::shared_ptr<Cloth> GetClothParentImplementation(ARCSim::Mesh& mesh_child) {
			for (auto cloth : cloths_in_scene_) {
				{
					if (cloth->mesh == mesh_child) {
						return cloth;
					}
				}

				return std::shared_ptr<Cloth>();
			}
		}
		void AddClothImplementation(std::shared_ptr<Cloth> cloth) { cloths_in_scene_.push_back(cloth); }

	private:
		std::vector<std::shared_ptr<Cloth>> cloths_in_scene_;

	};
}

#endif