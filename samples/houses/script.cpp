
#include "script.h"
#include <string>
#include <vector>
#include "Misc.h"
#include "sstream"

#include "Toasts.h"


#include "pugixml.hpp"

using namespace std;

const float menuX = 0.09f; //menuX 0.040
const float menuY = 0.02f; //menuY 0.68

Vector3 valentine = Misc::toVector3(-277.772, 807.117, 119.382);
Vector3 denis = Misc::toVector3(2507.318, -1301.392, 48.954);
Vector3 rhodes = Misc::toVector3(1359.132, -1300.011, 77.761);
Vector3 horn = Misc::toVector3(2907.984, 1308.881, 44.938);
Vector3 straw = Misc::toVector3(-1811.781, -353.537, 164.649);


Prompt PromptRoom;
Prompt PromptBuy;
Prompt Prompt_Buy;
Prompt Prompt_Locker;

Prompt Prompt_Back;
Prompt Prompt_Select;
Prompt Prompt_Menu;

Prompt Prompt_Sit;
Prompt Prompt_Sleep;

Prompt Prompt_Leave;
Prompt Prompt_Back2;
Prompt Prompt_Sleep2;

Prompt Prompt_Nap1;
Prompt Prompt_Nap2;
Prompt Prompt_Nap3;

const char* textLabel;

void initialize() {

	Misc::createPrompt(PromptRoom, "INPUT_INTERACT_OPTION1", "Buy Room ($2000)", 1);

	Misc::createPrompt(PromptBuy, "INPUT_INTERACT_OPTION1", "Buy Property ($18000)", 1);

	Misc::createPrompt(Prompt_Back, "INPUT_RELOAD", "Back", 2);

	Misc::createPrompt(Prompt_Select, "INPUT_FRONTEND_ACCEPT", "Select", 2);

	Misc::createPrompt(Prompt_Buy, "INPUT_FRONTEND_ACCEPT", "Buy", 1);

	Misc::createPrompt(Prompt_Menu, "INPUT_SHOP_BUY", "Customize Lot", 1);

	Misc::createPrompt(Prompt_Locker, "INPUT_SPRINT", "Weapon Locker", 1);



	Misc::createPrompt(Prompt_Sit, "INPUT_CONTEXT_X", "Sit", 0, -2019190071);
	Misc::createPrompt(Prompt_Sleep, "INPUT_SHOP_BUY", "Sleep", 0, -2019190071);

	Misc::createPrompt(Prompt_Sleep2, "INPUT_SHOP_BUY", "Sleep", 2, -2019190071);
	Misc::createPrompt(Prompt_Leave, "INPUT_RELOAD", "Leave", 2, -2019190071);

	//evening = 18
	//night = 24
	//morning = 6
	//noon = 12
	Misc::createPrompt(Prompt_Nap1, "INPUT_SHOP_BUY", "Evening", 2, -2019190071);

	Misc::createPrompt(Prompt_Nap2, "INPUT_JUMP", "Morning", 2, -2019190071);

	Misc::createPrompt(Prompt_Nap3, "INPUT_SPRINT", "Noon", 2, -2019190071);

	Misc::createPrompt(Prompt_Back2, "INPUT_RELOAD", "Back", 2, -2019190071);


}

bool is_sitting_bed = 0;

bool choose_sleep = 0;


bool is_in_sequence = 0;
void sleepSeq(int time) {


	is_in_sequence = 1;
	HUD::_HIDE_HUD_COMPONENT(-1679307491);
	if (!is_sitting_bed) {
		TASK::CLEAR_PED_TASKS(PLAYER::PLAYER_PED_ID(), 1, 1);
		TASK::TASK_START_SCENARIO_AT_POSITION(PLAYER::PLAYER_PED_ID(), MISC::GET_HASH_KEY("PROP_PLAYER_SLEEP_BED"), -327.35, 766.186, 121.2, 276.815, -1, true, false, 0, 0, false);

		WAIT(4000);
	}

	//WAIT(1000);

	CAM::DO_SCREEN_FADE_OUT(250);
	//CAM::DO_SCREEN_FADE_IN(0);

	
	

	AUDIO::TRIGGER_MUSIC_EVENT("SLEEP_TRANSITION_START");





	if (CLOCK::GET_CLOCK_HOURS() >= 5 && CLOCK::GET_CLOCK_HOURS() < 9) {
		GRAPHICS::ANIMPOSTFX_PLAY("skytl_0600_01clear");
	}
	if (CLOCK::GET_CLOCK_HOURS() >= 9 && CLOCK::GET_CLOCK_HOURS() < 12) {
		GRAPHICS::ANIMPOSTFX_PLAY("skytl_0900_01clear");
	}
	if (CLOCK::GET_CLOCK_HOURS() >= 12 && CLOCK::GET_CLOCK_HOURS() < 15) {
		GRAPHICS::ANIMPOSTFX_PLAY("skytl_1200_01clear");
	}
	if (CLOCK::GET_CLOCK_HOURS() >= 15 && CLOCK::GET_CLOCK_HOURS() < 23) {
		GRAPHICS::ANIMPOSTFX_PLAY("skytl_1500_03clouds");
	}
	if (CLOCK::GET_CLOCK_HOURS() >= 23 || (CLOCK::GET_CLOCK_HOURS() >= 0 && CLOCK::GET_CLOCK_HOURS() < 5)) {
		GRAPHICS::ANIMPOSTFX_PLAY("skytl_0000_01clear");
	}
	WAIT(1200);

	CAM::DO_SCREEN_FADE_IN(250);


	WAIT(1000);

	//TASK::_TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), MISC::GET_HASH_KEY("WORLD_PLAYER_SLEEP_BEDROLL"), -1, 1, 1, 1, 1);

	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1, 0);
	
		WAIT(2000);

		int tempTime = CLOCK::GET_CLOCK_HOURS() + time;
		if (tempTime >= 24) {
			tempTime -= 24;
		}

		CLOCK::ADVANCE_CLOCK_TIME_TO(tempTime, 0, 0);

		
		ATTRIBUTE::_SET_ATTRIBUTE_CORE_VALUE(PLAYER::PLAYER_PED_ID(), 1, ATTRIBUTE::_GET_ATTRIBUTE_CORE_VALUE(PLAYER::PLAYER_PED_ID(), 1) + (20 * time));


		WAIT(6000);



		AUDIO::TRIGGER_MUSIC_EVENT("SLEEP_TRANSITION_STOP");


		TASK::CLEAR_PED_TASKS(PLAYER::PLAYER_PED_ID(), 1, 1);

		//sitting = 1;

	
		HUD::_DISPLAY_HUD_COMPONENT(-1679307491);

		
		is_sitting_bed = 0;

		choose_sleep = 0;

		AnimScene anims;

	//	if (func_126() && !CAM::IS_FIRST_PERSON_CAMERA_ACTIVE(1, 0, 0))
		//{
			anims = ANIMSCENE::_CREATE_ANIM_SCENE("script@mech@player_sleep_bed", 0, "pbl_hat_action", false, true);
	//	}
		//else
		//{
		//	anims = ANIMSCENE::_CREATE_ANIM_SCENE("script@mech@player_sleep_bed", 0, "pbl_no_hat_action", false, true);
		//}
		
		
		ANIMSCENE::LOAD_ANIM_SCENE(anims);
		ANIMSCENE::SET_ANIM_SCENE_ENTITY(anims, "player", PLAYER::PLAYER_PED_ID(), 0);
		Vector3 testVec = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0, 0);
		ANIMSCENE::SET_ANIM_SCENE_ORIGIN(anims, testVec.x, testVec.y, testVec.z, 0.f, 0.f, 279, 2);
		ANIMSCENE::START_ANIM_SCENE(anims);



}





const int houseLimit = 8;

// 0 - saint denis room  1 - ridge view;  2 - house near strawberry; 3 - valentine saloon room
int Houses[houseLimit] = { 0, 0, 0, 0, 0, 0, 0, 0 };
Vector3 housesVecs[houseLimit] = { Misc::toVector3(2637.955, -1222.115, 59.601), Misc::toVector3(1784.152, 462.975, 113.038), Misc::toVector3(-1551.511, 253.352, 114.799), Misc::toVector3(-312.422, 816.597, 121.728), Misc::toVector3(-1819.247, -367.570, 166.506), Misc::toVector3(1331.634, -1371.821, 79.870), Misc::toVector3(-326.072, 765.827, 117.434), Misc::toVector3(1455.307, -1578.889, 72.016) };
Vector3 housesBuy[houseLimit] = { Misc::toVector3(2637.955, -1222.115, 59.601), Misc::toVector3(1702.191, 495.829, 103.779), Misc::toVector3(-1620.814, 234.926, 106.045), Misc::toVector3(-312.422, 816.597, 121.728), Misc::toVector3(-1819.247, -367.570, 166.506), Misc::toVector3(1331.634, -1371.821, 79.870), Misc::toVector3(-326.072, 765.827, 117.434), Misc::toVector3(1407.823, -1637.419, 67.904) };
int housesPrice[houseLimit] = { 3000, 18000, 12000, 1500, 2000, 2500, 2300, 10300 };
int housesBlip[houseLimit] = { };




int select_clock;

int menu_on;

int current_cell;


Cam houseCam;
Cam outsideCam;

Cam room1Cam;
Cam room2Cam;
Cam room3Cam;
Cam room4Cam;
Cam room5Cam;
Cam room6Cam;

Cam outside1Cam;
Cam outside2Cam;
Cam outside3Cam;
Cam outside4Cam;
Cam outside5Cam;


//Cam houseCam2;
//Cam outsideCam2;



//Cam houseCam3;
//Cam outsideCam3;





Vector3 LocalCameraVec;
Vector3 LocalCameraVecPoint;



int ObjectHash;
float ObjectPosX;
float ObjectPosY;
float ObjectPosZ;

float ObjectRotX;
float ObjectRotY;
float ObjectRotZ;

bool ObjectCollision;
bool ObjectDynamic;

vector<Object> tempObjects;

vector<Object> mainObjects;

bool once = 0;


bool ridgeRooms[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };


bool strawRooms[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };


bool argilRooms[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


void Save()
{
	//save
	ofstream SaveFile;
	SaveFile.open("Houses.dat", std::ofstream::out);

	for (int i = 0; i < houseLimit; i++) {
		SaveFile << Houses[i] << " ";
	}

	for (int i = 0; i < 9; i++) {
		SaveFile << ridgeRooms[i] << " ";
	}

	for (int i = 0; i < 9; i++) {
		SaveFile << strawRooms[i] << " ";
	}

	for (int i = 0; i < 10; i++) {
		SaveFile << argilRooms[i] << " ";
	}

	SaveFile.close();

}


void Load()
{
	ifstream LoadFile;
	LoadFile.open("Houses.dat", std::ifstream::in);


	for (int i = 0; i < houseLimit; i++) {
		LoadFile >> Houses[i];
	}

	for (int i = 0; i < 9; i++) {
		LoadFile >> ridgeRooms[i];
	}

	for (int i = 0; i < 9; i++) {
		LoadFile >> strawRooms[i];
	}

	for (int i = 0; i < 10; i++) {
		LoadFile >> argilRooms[i];
	}

	LoadFile.close();
}


void Room(string path, vector<Object>& stdvector) {
	if (once == 0) {
		//CAM::POINT_CAM_AT_COORD(houseCam, 1781.976f, 461.595f, 112.006f);
		//CAM::RENDER_SCRIPT_CAMS(1, 1, 500, 1, 0, 0);
		//CAM::SET_CAM_ACTIVE(houseCam, 1);


		const std::string FilePath = path;
		pugi::xml_document MapFile;
		if (MapFile.load_file(FilePath.c_str()).status != pugi::status_ok)
		{
			Misc::showSubtitle("the maps couldn't be ~COLOR_GOLD~loaded ~COLOR_WHITE~in, make sure you installed the mod correctly");

		}


		for (auto& ObjectChild : MapFile.select_nodes("//Map/Object"))
		{
			pugi::xml_node MapObjectsIterator = ObjectChild.node();
			pugi::xml_attribute Valid = MapObjectsIterator.attribute("Hash");
			if (Valid != nullptr)
			{
				ObjectHash = MapObjectsIterator.attribute("Hash").as_int();
				// spawn the object and do other stuff
			}

			Valid = MapObjectsIterator.attribute("Position_x");
			if (Valid != nullptr)
			{
				ObjectPosX = MapObjectsIterator.attribute("Position_x").as_float();
			}

			Valid = MapObjectsIterator.attribute("Position_y");
			if (Valid != nullptr)
			{
				ObjectPosY = MapObjectsIterator.attribute("Position_y").as_float();
			}

			Valid = MapObjectsIterator.attribute("Position_z");
			if (Valid != nullptr)
			{
				ObjectPosZ = MapObjectsIterator.attribute("Position_z").as_float();
			}



			Valid = MapObjectsIterator.attribute("Rotation_x");
			if (Valid != nullptr)
			{
				ObjectRotX = MapObjectsIterator.attribute("Rotation_x").as_float();
			}

			Valid = MapObjectsIterator.attribute("Rotation_y");
			if (Valid != nullptr)
			{
				ObjectRotY = MapObjectsIterator.attribute("Rotation_y").as_float();
			}

			Valid = MapObjectsIterator.attribute("Rotation_z");
			if (Valid != nullptr)
			{
				ObjectRotZ = MapObjectsIterator.attribute("Rotation_z").as_float();
			}

			Valid = MapObjectsIterator.attribute("Rotation_z");
			if (Valid != nullptr)
			{
				ObjectRotZ = MapObjectsIterator.attribute("Rotation_z").as_float();
			}



			Valid = MapObjectsIterator.attribute("Collision");
			if (Valid != nullptr)
			{
				ObjectCollision = MapObjectsIterator.attribute("Collision").as_bool();
			}

			Valid = MapObjectsIterator.attribute("Dynamic");
			if (Valid != nullptr)
			{
				ObjectDynamic = MapObjectsIterator.attribute("Dynamic").as_bool();
			}




			Vector3 ObjectRot = Misc::toVector3(ObjectRotX, ObjectRotY, ObjectRotZ);
			Vector3 ObjectPos = Misc::toVector3(ObjectPosX, ObjectPosY, ObjectPosZ);

			Object tempObj = Misc::createProp(ObjectHash, ObjectPos, ObjectRot, 0, ObjectCollision, 0);

			stdvector.push_back(tempObj);




		}






		once = 1;
	}
}



int menu_controls(int number_of_cells) {

	//dpad controls
	if (PAD::IS_CONTROL_JUST_PRESSED(0, MISC::GET_HASH_KEY("INPUT_FRONTEND_UP"))) {

		AUDIO::PLAY_SOUND_FRONTEND("NAV_RIGHT", "PAUSE_MENU_SOUNDSET", 1, 0);

		vector<Object>::iterator objItr;
		for (objItr = tempObjects.begin(); objItr != tempObjects.end(); objItr++)
		{
			Object curr = *objItr;
			OBJECT::DELETE_OBJECT(&curr);

		}

		once = 0;
		current_cell--;
		if (current_cell < 0) {
			current_cell = number_of_cells;
		}
	}

	if (PAD::IS_CONTROL_JUST_PRESSED(0, MISC::GET_HASH_KEY("INPUT_FRONTEND_DOWN"))) {

		AUDIO::PLAY_SOUND_FRONTEND("NAV_LEFT", "PAUSE_MENU_SOUNDSET", 1, 0);


		vector<Object>::iterator objItr;
		for (objItr = tempObjects.begin(); objItr != tempObjects.end(); objItr++)
		{
			Object curr = *objItr;
			OBJECT::DELETE_OBJECT(&curr);

		}


		once = 0;
		current_cell++;
		if (current_cell > number_of_cells) {
			current_cell = 0;



		}
	}






	return current_cell;
}


void BuyRoom(string path, vector<Object>& stdvector) {

	vector<Object>::iterator objItr;
	for (objItr = tempObjects.begin(); objItr != tempObjects.end(); objItr++)
	{
		Object curr = *objItr;
		OBJECT::DELETE_OBJECT(&curr);

	}


	const std::string FilePath = path;
	pugi::xml_document MapFile;
	if (MapFile.load_file(FilePath.c_str()).status != pugi::status_ok)
	{
		Misc::showSubtitle("the map couldn't be ~COLOR_GOLD~loaded ~COLOR_WHITE~in, make sure you installed the mod correctly");

	}


	for (auto& ObjectChild : MapFile.select_nodes("//Map/Object"))
	{
		pugi::xml_node MapObjectsIterator = ObjectChild.node();
		pugi::xml_attribute Valid = MapObjectsIterator.attribute("Hash");
		if (Valid != nullptr)
		{
			ObjectHash = MapObjectsIterator.attribute("Hash").as_int();
			// spawn the object and do other stuff
		}

		Valid = MapObjectsIterator.attribute("Position_x");
		if (Valid != nullptr)
		{
			ObjectPosX = MapObjectsIterator.attribute("Position_x").as_float();
		}

		Valid = MapObjectsIterator.attribute("Position_y");
		if (Valid != nullptr)
		{
			ObjectPosY = MapObjectsIterator.attribute("Position_y").as_float();
		}

		Valid = MapObjectsIterator.attribute("Position_z");
		if (Valid != nullptr)
		{
			ObjectPosZ = MapObjectsIterator.attribute("Position_z").as_float();
		}



		Valid = MapObjectsIterator.attribute("Rotation_x");
		if (Valid != nullptr)
		{
			ObjectRotX = MapObjectsIterator.attribute("Rotation_x").as_float();
		}

		Valid = MapObjectsIterator.attribute("Rotation_y");
		if (Valid != nullptr)
		{
			ObjectRotY = MapObjectsIterator.attribute("Rotation_y").as_float();
		}

		Valid = MapObjectsIterator.attribute("Rotation_z");
		if (Valid != nullptr)
		{
			ObjectRotZ = MapObjectsIterator.attribute("Rotation_z").as_float();
		}


		Valid = MapObjectsIterator.attribute("Collision");
		if (Valid != nullptr)
		{
			ObjectCollision = MapObjectsIterator.attribute("Collision").as_bool();
		}

		Valid = MapObjectsIterator.attribute("Dynamic");
		if (Valid != nullptr)
		{
			ObjectDynamic = MapObjectsIterator.attribute("Dynamic").as_bool();
		}






		Vector3 ObjectRot = Misc::toVector3(ObjectRotX, ObjectRotY, ObjectRotZ);
		Vector3 ObjectPos = Misc::toVector3(ObjectPosX, ObjectPosY, ObjectPosZ);

		Object tempObj = Misc::createProp(ObjectHash, ObjectPos, ObjectRot, 0, ObjectCollision, ObjectDynamic);

		stdvector.push_back(tempObj);




	}






	once = 1;
}


Cam localCam;

void Menu() {

	if (menu_on > 0) {


		HUD::_UIPROMPT_SET_ENABLED(Prompt_Menu, 0);
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Menu, 0);

		HUD::HIDE_HUD_AND_RADAR_THIS_FRAME();

		HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 1);
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 1);

		HUD::_UIPROMPT_SET_ENABLED(Prompt_Back, 1);
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Back, 1);


		Misc::drawSprite("generic_textures", "inkroller_1a", menuX - 0.05f, menuY + 0.05, 0.27, 0.9f, 0, 0, 0, 0, 230);

		Misc::drawSprite("generic_textures", "menu_header_1a", menuX - 0.015, menuY + 0.08, 0.2, 0.1f, 0, 255, 255, 255, 255);
		Misc::drawText("Ridge View", menuX + 0.09, menuY + 0.105, 255, 255, 255, 255, 1, 0.7f, 0.7f);




		if (menu_on == 1) {

			if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Back)) {
				

				AUDIO::PLAY_SOUND_FRONTEND("BACK", "HUD_SHOP_SOUNDSET", 1, 0);

				//TASK::CLEAR_PED_TASKS(player, 1, 1);



				CAM::RENDER_SCRIPT_CAMS(0, 0, 500, 1, 0, 0);
				CAM::SET_CAM_ACTIVE(localCam, 0);

				vector<Object>::iterator objItr;
				for (objItr = tempObjects.begin(); objItr != tempObjects.end(); objItr++)
				{
					Object curr = *objItr;
					OBJECT::DELETE_OBJECT(&curr); //TEMP!!!!

				}

				ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), 1);

				current_cell = 0;
				if (menu_on > 1) {
					menu_on = 1;
				}
				else {
					menu_on = 0;
					TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID(), 1, 1);
					CAM::DESTROY_CAM(room1Cam, 1);
					CAM::DESTROY_CAM(room2Cam, 1);
					CAM::DESTROY_CAM(room3Cam, 1);
					CAM::DESTROY_CAM(room4Cam, 1);
					CAM::DESTROY_CAM(room5Cam, 1);
					CAM::DESTROY_CAM(room6Cam, 1);

					CAM::DESTROY_CAM(outside1Cam, 1);
					CAM::DESTROY_CAM(outside2Cam, 1);
					CAM::DESTROY_CAM(outside3Cam, 1);
					CAM::DESTROY_CAM(outside4Cam, 1);

					CAM::DESTROY_CAM(localCam, 1);

					CAM::DESTROY_CAM(houseCam, 1);
					CAM::DESTROY_CAM(outsideCam, 1);

				}


				return;
			}



			HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);

			Misc::drawTextSmall("Interior", menuX + 0.021, menuY + 0.26f, 255, 255, 255, 200, 1, 0.4f, 0.4f);
			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148, menuY + 0.25f, 0.2, 0.05f, 0, 60, 60, 60, 100);

			Misc::drawTextSmall("Outside", menuX + 0.02, menuY + 0.26f + 0.052, 255, 255, 255, 200, 1, 0.4f, 0.4f);
			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148, menuY + 0.25f + 0.052, 0.2, 0.052f, 0, 60, 60, 60, 100);

			Misc::drawSprite("generic_textures", "menu_bar", menuX - 0.0135, menuY + 0.35f, 0.2, 0.0025f, 0, 255, 255, 255, 120);







			float selectY = -0.013f + (0.0525f * menu_controls(1));
			Misc::drawSprite("menu_textures", "crafting_highlight_l", menuX + 0.294 - 0.315f, menuY + 0.123f + selectY + 0.142f, 0.0135, 0.05f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_r", menuX + 0.492 - 0.315f, menuY + 0.123f + selectY + 0.142f, 0.0135, 0.05f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_b", menuX + 0.3 - 0.315f, menuY + 0.1f + selectY + 0.142f, 0.2, 0.03f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_t", menuX + 0.3 - 0.315f, menuY + 0.165f + selectY + 0.142f, 0.2, 0.03f, 0, 255, 0, 0, 250);





			//drawText("cabin", menuX + 0.085, menuY + 0.2f, 255, 255, 255, 255, 1, 0.5f, 0.5f);

			Misc::drawSprite("generic_textures", "menu_bar", menuX - 0.0135, menuY + 0.88f, 0.2, 0.0025f, 0, 255, 255, 255, 120);



			Misc::drawText("Upgrades", menuX + 0.085, menuY + 0.19f, 255, 255, 255, 255, 1, 0.45f, 0.45f);






			select_clock++;
			if (select_clock > 10) {


				if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Select))
				{

					AUDIO::PLAY_SOUND_FRONTEND("INFO", "HUD_SHOP_SOUNDSET", 1, 0);

					//menu_on = 0;
					menu_on = 0;

					switch (current_cell) {
					case 0:
						menu_on = 2;

						current_cell = 0;

						CAM::DESTROY_CAM(room1Cam, 1);
						CAM::DESTROY_CAM(room2Cam, 1);
						CAM::DESTROY_CAM(room3Cam, 1);
						CAM::DESTROY_CAM(room4Cam, 1);

						room1Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1788.470, 465.166, 114.072, 0, 0, 0, 60, 1, 2);
						room2Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1784.488, 461.218, 113.984, 0, 0, 0, 60, 1, 2);
						room3Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1780.750f, 457.612f, 114.019f, 0, 0, 0, 60, 1, 2);
						room4Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1787.372f, 461.520f, 114.019f, 0, 0, 0, 60, 1, 2);



						break;
					case 1:
						menu_on = 3;

						current_cell = 0;

						CAM::DESTROY_CAM(outside1Cam, 1);
						CAM::DESTROY_CAM(outside2Cam, 1);
						CAM::DESTROY_CAM(outside3Cam, 1);
						CAM::DESTROY_CAM(outside4Cam, 1);
						CAM::DESTROY_CAM(outside5Cam, 1);

						outside1Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1773.002, 460.635, 114.404, 0, 0, 0, 60, 1, 2);
						outside2Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1782.116, 448.621, 114.349, 0, 0, 0, 60, 1, 2);
						outside3Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1752.424f, 443.926f, 114.179f, 0, 0, 0, 60, 1, 2);
						outside4Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1778.572, 526.340, 108.713, 0, 0, 0, 60, 1, 2);
						outside5Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1780.441f, 451.111f, 114.179f, 0, 0, 0, 60, 1, 2);



						break;



					};
					select_clock = 0;
				}



			}



			if (current_cell == 0) {
				//LocalCameraVec = toVector3(1774.191, 456.f, 114.f);
				LocalCameraVecPoint = Misc::toVector3(1779.585, 464.1, 113.f);

				localCam = houseCam;
			}
			if (current_cell == 1) {
				//LocalCameraVec = toVector3(1774.191, 454.802, 112.283);
				LocalCameraVecPoint = Misc::toVector3(1758.168, 446.411, 111.317);
				//CAM::RENDER_SCRIPT_CAMS(0, 1, 500, 1, 0, 0);

				localCam = outsideCam;
			}


		}


		if (menu_on == 2) {

			if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Back)) {
				

				AUDIO::PLAY_SOUND_FRONTEND("BACK", "HUD_SHOP_SOUNDSET", 1, 0);

				current_cell = 0;

				menu_on = 1;

			}



			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148, menuY + 0.25f, 0.2, 0.05f, 0, 60, 60, 60, 100);


			Misc::drawTextSmall("Bedroom", menuX + 0.021, menuY + 0.262f, 255, 255, 255, 255, 1, 0.4f, 0.4f);
			if (!ridgeRooms[0]) {
				Misc::drawText("$324", menuX + 0.021 + 0.135, menuY + 0.26f, 255, 255, 255, 255, 1, 0.55f, 0.55f);
			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}





			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148, menuY + 0.25f + 0.052, 0.2, 0.052f, 0, 60, 60, 60, 100);


			Misc::drawTextSmall("Office", menuX + 0.014, menuY + 0.262f + 0.052, 255, 255, 255, 255, 1, 0.4f, 0.4f);

			if (!ridgeRooms[1]) {
				Misc::drawText("$275", menuX + 0.021 + 0.135, menuY + 0.26f + 0.052, 255, 255, 255, 255, 1, 0.55f, 0.55f);
			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f + 0.052, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}





			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148f, menuY + 0.25f + 0.104f, 0.2, 0.052f, 0, 60, 60, 60, 100);


			Misc::drawTextSmall("Living room", menuX + 0.032, menuY + 0.262f + 0.104f, 255, 255, 255, 255, 1, 0.4f, 0.4f);

			if (!ridgeRooms[2]) {
				Misc::drawText("$468", menuX + 0.021 + 0.135, menuY + 0.26f + 0.104f, 255, 255, 255, 255, 1, 0.55f, 0.55f);

			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f + 0.104f, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}



			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148f, menuY + 0.25f + 0.156f, 0.2, 0.052f, 0, 60, 60, 60, 100);


			Misc::drawTextSmall("Weapon Locker", menuX + 0.04, menuY + 0.262f + 0.156f, 255, 255, 255, 255, 1, 0.4f, 0.4f);

			if (!ridgeRooms[8]) {
				Misc::drawText("$165", menuX + 0.021 + 0.135, menuY + 0.26f + 0.156f, 255, 255, 255, 255, 1, 0.55f, 0.55f);

			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f + 0.156f, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}





			//0.88
			Misc::drawSprite("generic_textures", "menu_bar", menuX - 0.0135, menuY + 0.88f, 0.2, 0.0025f, 0, 255, 255, 255, 120);



			Misc::drawSprite("generic_textures", "menu_bar", menuX - 0.0135, menuY + 0.458f, 0.2, 0.0025f, 0, 255, 255, 255, 120);


			Misc::drawSprite("generic_textures", "menu_bar", menuX - 0.0135, menuY + 0.25f, 0.2, 0.0025f, 0, 255, 255, 255, 120);


			float selectY = -0.013f + (0.0525f * menu_controls(3));
			Misc::drawSprite("menu_textures", "crafting_highlight_l", menuX + 0.294 - 0.315f, menuY + 0.123f + selectY + 0.142f, 0.0135, 0.05f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_r", menuX + 0.492 - 0.315f, menuY + 0.123f + selectY + 0.142f, 0.0135, 0.05f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_b", menuX + 0.3 - 0.315f, menuY + 0.1f + selectY + 0.142f, 0.2, 0.03f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_t", menuX + 0.3 - 0.315f, menuY + 0.165f + selectY + 0.142f, 0.2, 0.03f, 0, 255, 0, 0, 250);





			Misc::drawText("Upgrades", menuX + 0.085, menuY + 0.19f, 255, 255, 255, 255, 1, 0.45f, 0.45f);



			HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 0);
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 0);

			HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 1);
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 1);


			select_clock++;
			if (select_clock > 10) {


				if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Buy))
				{
					

					AUDIO::PLAY_SOUND_FRONTEND("PURCHASE", "Ledger_Sounds", 1, 0);



					//menu_on = 0;


					switch (menu_controls(2)) {
					case 0:
						ridgeRooms[0] = 1;
						BuyRoom("Houses/ridge_bedroom.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(32400);
						break;
					case 1:
						ridgeRooms[1] = 1;
						BuyRoom("Houses/ridge_study.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(27500);
						break;
					case 2:
						ridgeRooms[2] = 1;
						BuyRoom("Houses/ridge_livingroom.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(46800);
						break;
					case 3:
						ridgeRooms[8] = 1;
						BuyRoom("Houses/ridge_gunlocker.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(16500);
						break;

					};
					select_clock = 0;
				}



			}



			if (current_cell == 0) {
				LocalCameraVecPoint = Misc::toVector3(1786.133, 466.301, 112.024);
				if (!ridgeRooms[0]) {
					Room("Houses/ridge_bedroom.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 32400) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
						//HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}
				localCam = room1Cam;
			}
			if (current_cell == 1) {
				LocalCameraVecPoint = Misc::toVector3(1788.657, 460.122, 112.068);
				if (!ridgeRooms[1]) {
					Room("Houses/ridge_study.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 27500) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}
				localCam = room2Cam;
			}
			if (current_cell == 2) {
				LocalCameraVecPoint = Misc::toVector3(1781.976f, 461.595f, 112.006f);
				if (!ridgeRooms[2]) {
					Room("Houses/ridge_livingroom.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 46800) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}
				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}
				localCam = room3Cam;
			}
			if (current_cell == 3) {
				LocalCameraVecPoint = Misc::toVector3(1785.533f, 460.536f, 113.040f);
				if (!ridgeRooms[8]) {
					Room("Houses/ridge_gunlocker.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 16500) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}
				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}
				localCam = room4Cam;
			}

		}


		if (menu_on == 3) {

			if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Back)) {

				AUDIO::PLAY_SOUND_FRONTEND("BACK", "HUD_SHOP_SOUNDSET", 1, 0);

				current_cell = 0;

				menu_on = 1;

			}

			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148, menuY + 0.25f, 0.2, 0.05f, 0, 60, 60, 60, 100);


			Misc::drawTextSmall("Hitching Post", menuX + 0.031, menuY + 0.262f, 255, 255, 255, 255, 1, 0.4f, 0.4f);
			if (!ridgeRooms[3]) {
				Misc::drawText("$65", menuX + 0.021 + 0.135, menuY + 0.26f, 255, 255, 255, 255, 1, 0.55f, 0.55f);
			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}





			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148, menuY + 0.25f + 0.052, 0.2, 0.052f, 0, 60, 60, 60, 100);


			Misc::drawTextSmall("Campfire", menuX + 0.02, menuY + 0.262f + 0.052, 255, 255, 255, 255, 1, 0.4f, 0.4f);

			if (!ridgeRooms[4]) {
				Misc::drawText("$125", menuX + 0.021 + 0.135, menuY + 0.26f + 0.052, 255, 255, 255, 255, 1, 0.55f, 0.55f);
			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f + 0.052, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}





			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148f, menuY + 0.25f + 0.104f, 0.2, 0.052f, 0, 60, 60, 60, 100);


			Misc::drawTextSmall("Chicken Coop", menuX + 0.032, menuY + 0.262f + 0.104f, 255, 255, 255, 255, 1, 0.4f, 0.4f);

			if (!ridgeRooms[5]) {
				Misc::drawText("$250", menuX + 0.021 + 0.135, menuY + 0.26f + 0.104f, 255, 255, 255, 255, 1, 0.55f, 0.55f);

			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f + 0.104f, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}




			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148f, menuY + 0.25f + 0.156f, 0.2, 0.052f, 0, 60, 60, 60, 100);


			Misc::drawTextSmall("Outdoorsman Bundle", menuX + 0.053, menuY + 0.262f + 0.156f, 255, 255, 255, 255, 1, 0.4f, 0.4f);

			if (!ridgeRooms[6]) {
				Misc::drawText("$120", menuX + 0.021 + 0.135, menuY + 0.26f + 0.156f, 255, 255, 255, 255, 1, 0.55f, 0.55f);

			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f + 0.156f, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}


			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148f, menuY + 0.25f + 0.208f, 0.2, 0.052f, 0, 60, 60, 60, 100);


			Misc::drawTextSmall("Workshop", menuX + 0.024, menuY + 0.262f + 0.208f, 255, 255, 255, 255, 1, 0.4f, 0.4f);

			if (!ridgeRooms[7]) {
				Misc::drawText("$430", menuX + 0.021 + 0.135, menuY + 0.26f + 0.208f, 255, 255, 255, 255, 1, 0.55f, 0.55f);

			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f + 0.208f, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}









			Misc::drawSprite("generic_textures", "menu_bar", menuX - 0.0135, menuY + 0.88f, 0.2, 0.0025f, 0, 255, 255, 255, 120);



			Misc::drawSprite("generic_textures", "menu_bar", menuX - 0.0135, menuY + 0.405f + 0.105f, 0.2, 0.0025f, 0, 255, 255, 255, 120);


			Misc::drawSprite("generic_textures", "menu_bar", menuX - 0.0135, menuY + 0.25f, 0.2, 0.0025f, 0, 255, 255, 255, 120);


			float selectY = -0.013f + (0.0525f * menu_controls(4));
			Misc::drawSprite("menu_textures", "crafting_highlight_l", menuX + 0.294 - 0.315f, menuY + 0.123f + selectY + 0.142f, 0.0135, 0.05f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_r", menuX + 0.492 - 0.315f, menuY + 0.123f + selectY + 0.142f, 0.0135, 0.05f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_b", menuX + 0.3 - 0.315f, menuY + 0.1f + selectY + 0.142f, 0.2, 0.03f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_t", menuX + 0.3 - 0.315f, menuY + 0.165f + selectY + 0.142f, 0.2, 0.03f, 0, 255, 0, 0, 250);





			Misc::drawText("Upgrades", menuX + 0.085, menuY + 0.19f, 255, 255, 255, 255, 1, 0.45f, 0.45f);



			HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 0);
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 0);

			HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 1);
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 1);


			select_clock++;
			if (select_clock > 10) {


				if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Buy))
				{
		
					AUDIO::PLAY_SOUND_FRONTEND("PURCHASE", "Ledger_Sounds", 1, 0);



					//menu_on = 0;


					switch (current_cell) {
					case 0:
						ridgeRooms[3] = 1;
						BuyRoom("Houses/ridge_hitchingpost.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(6500);
						break;
					case 1:
						ridgeRooms[4] = 1;
						BuyRoom("Houses/ridge_campfire.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(12500);
						break;
					case 2:
						ridgeRooms[5] = 1;
						BuyRoom("Houses/ridge_farmers.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(25000);
						break;

					case 3:
						ridgeRooms[6] = 1;
						BuyRoom("Houses/ridge_nature.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(12000);
						break;
					case 4:
						ridgeRooms[7] = 1;
						BuyRoom("Houses/ridge_outdoorsman.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(43000);
						break;


					};
					select_clock = 0;
				}



			}



			if (current_cell == 0) {
				LocalCameraVecPoint = Misc::toVector3(1776.0, 463.333, 112.606f);

				localCam = outside1Cam;
				if (!ridgeRooms[3]) {
					Room("Houses/ridge_hitchingpost.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 6500) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}

			}
			if (current_cell == 1) {
				LocalCameraVecPoint = Misc::toVector3(1783.585, 450.527, 112.548f);

				localCam = outside2Cam;
				if (!ridgeRooms[4]) {
					Room("Houses/ridge_campfire.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 12500) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}

			}
			if (current_cell == 2) {
				LocalCameraVecPoint = Misc::toVector3(1750.254f, 439.070f, 111.138f);

				localCam = outside3Cam;
				if (!ridgeRooms[5]) {
					Room("Houses/ridge_farmers.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 25000) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}

			}


			if (current_cell == 3) {
				LocalCameraVecPoint = Misc::toVector3(1780.953f, 524.5f, 107.522f);

				localCam = outside4Cam;
				if (!ridgeRooms[6]) {
					Room("Houses/ridge_nature.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 12000) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}

			}
			if (current_cell == 4) {
				LocalCameraVecPoint = Misc::toVector3(1781.424, 456.034, 112.748f);

				localCam = outside5Cam;
				if (!ridgeRooms[7]) {
					Room("Houses/ridge_outdoorsman.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 43000) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}

			}





		}











		CAM::POINT_CAM_AT_COORD(localCam, LocalCameraVecPoint.x, LocalCameraVecPoint.y, LocalCameraVecPoint.z);
		CAM::RENDER_SCRIPT_CAMS(1, 1, 500, 1, 0, 0);
		CAM::SET_CAM_ACTIVE(localCam, 1);

	}

}
//1780.750f, 457.612f, 114.019f interior coords


void Menu2() {

	if (menu_on > 0) {


		HUD::_UIPROMPT_SET_ENABLED(Prompt_Menu, 0);
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Menu, 0);

		HUD::HIDE_HUD_AND_RADAR_THIS_FRAME();

		HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 1);
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 1);

		HUD::_UIPROMPT_SET_ENABLED(Prompt_Back, 1);
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Back, 1);


		Misc::drawSprite("generic_textures", "inkroller_1a", menuX - 0.05f, menuY + 0.05, 0.27, 0.9f, 0, 0, 0, 0, 230);

		Misc::drawSprite("generic_textures", "menu_header_1a", menuX - 0.015, menuY + 0.08, 0.2, 0.1f, 0, 255, 255, 255, 255);
		Misc::drawText("Shepherds Rise", menuX + 0.09, menuY + 0.105, 255, 255, 255, 255, 1, 0.7f, 0.7f);




		if (menu_on == 1) {

			if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Back)) {
				

				AUDIO::PLAY_SOUND_FRONTEND("BACK", "HUD_SHOP_SOUNDSET", 1, 0);

				TASK::CLEAR_PED_TASKS(PLAYER::PLAYER_PED_ID(), 1, 1);

				CAM::RENDER_SCRIPT_CAMS(0, 0, 500, 1, 0, 0);
				CAM::SET_CAM_ACTIVE(localCam, 0);

				vector<Object>::iterator objItr;
				for (objItr = tempObjects.begin(); objItr != tempObjects.end(); objItr++)
				{
					Object curr = *objItr;
					OBJECT::DELETE_OBJECT(&curr); //TEMP!!!!

				}

				ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), 1);

				current_cell = 0;
				if (menu_on > 1) {
					menu_on = 1;
				}
				else {
					menu_on = 0;
					TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID(), 1, 1);
					CAM::DESTROY_CAM(room1Cam, 1);
					CAM::DESTROY_CAM(room2Cam, 1);
					CAM::DESTROY_CAM(room3Cam, 1);
					CAM::DESTROY_CAM(room4Cam, 1);
					CAM::DESTROY_CAM(room5Cam, 1);
					CAM::DESTROY_CAM(room6Cam, 1);

					CAM::DESTROY_CAM(outside1Cam, 1);
					CAM::DESTROY_CAM(outside2Cam, 1);
					CAM::DESTROY_CAM(outside3Cam, 1);
					CAM::DESTROY_CAM(outside4Cam, 1);

					CAM::DESTROY_CAM(localCam, 1);

					CAM::DESTROY_CAM(houseCam, 1);
					CAM::DESTROY_CAM(outsideCam, 1);


				}

				
				return;
			}



			HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);

			Misc::drawTextSmall("Interior", menuX + 0.021, menuY + 0.26f, 255, 255, 255, 200, 1, 0.4f, 0.4f);
			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148, menuY + 0.25f, 0.2, 0.05f, 0, 60, 60, 60, 100);

			Misc::drawTextSmall("Outside", menuX + 0.02, menuY + 0.26f + 0.052, 255, 255, 255, 200, 1, 0.4f, 0.4f);
			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148, menuY + 0.25f + 0.052, 0.2, 0.052f, 0, 60, 60, 60, 100);

			Misc::drawSprite("generic_textures", "menu_bar", menuX - 0.0135, menuY + 0.35f, 0.2, 0.0025f, 0, 255, 255, 255, 120);







			float selectY = -0.013f + (0.0525f * menu_controls(1));
			Misc::drawSprite("menu_textures", "crafting_highlight_l", menuX + 0.294 - 0.315f, menuY + 0.123f + selectY + 0.142f, 0.0135, 0.05f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_r", menuX + 0.492 - 0.315f, menuY + 0.123f + selectY + 0.142f, 0.0135, 0.05f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_b", menuX + 0.3 - 0.315f, menuY + 0.1f + selectY + 0.142f, 0.2, 0.03f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_t", menuX + 0.3 - 0.315f, menuY + 0.165f + selectY + 0.142f, 0.2, 0.03f, 0, 255, 0, 0, 250);






			Misc::drawText("Upgrades", menuX + 0.085, menuY + 0.19f, 255, 255, 255, 255, 1, 0.45f, 0.45f);


			Misc::drawSprite("generic_textures", "menu_bar", menuX - 0.0135, menuY + 0.88f, 0.2, 0.0025f, 0, 255, 255, 255, 120);







			select_clock++;
			if (select_clock > 10) {


				if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Select))
				{
					

					AUDIO::PLAY_SOUND_FRONTEND("INFO", "HUD_SHOP_SOUNDSET", 1, 0);

					//menu_on = 0;
					menu_on = 0;

					switch (current_cell) {
					case 0:
						menu_on = 2;

						current_cell = 0;

						CAM::DESTROY_CAM(room1Cam, 1);
						CAM::DESTROY_CAM(room2Cam, 1);
						CAM::DESTROY_CAM(room3Cam, 1);
						CAM::DESTROY_CAM(room4Cam, 1);
						CAM::DESTROY_CAM(room5Cam, 1);


						room1Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", -1548.019, 258.829, 114.799f, 0, 0, 0, 60, 1, 2);
						room2Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", -1548.518, 250.364, 115.799f, 0, 0, 0, 60, 1, 2);
						room3Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", -1554.520f, 248.148f, 114.799f, 0, 0, 0, 60, 1, 2);
						room4Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", -1552.170f, 256.280f, 114.799f, 0, 0, 0, 60, 1, 2);
						room5Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", -1548.767f, 256.069f, 114.799f, 0, 0, 0, 60, 1, 2);



						break;
					case 1:
						menu_on = 3;

						current_cell = 0;

						CAM::DESTROY_CAM(outside1Cam, 1);
						CAM::DESTROY_CAM(outside2Cam, 1);
						CAM::DESTROY_CAM(outside3Cam, 1);
						CAM::DESTROY_CAM(outside4Cam, 1);



						outside1Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", -1560.001, 243.963, 114.704, 0, 0, 0, 60, 1, 2);
						outside2Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", -1564.904, 271.082, 114.235, 0, 0, 0, 60, 1, 2);
						outside3Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", -1555.942f, 252.036f, 114.779f, 0, 0, 0, 60, 1, 2);
						outside4Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", -1546.898f, 247.510f, 113.977f, 0, 0, 0, 60, 1, 2);



						break;



					};
					select_clock = 0;
				}



			}



			if (current_cell == 0) {
				//LocalCameraVec = toVector3(1774.191, 456.f, 114.f);
				LocalCameraVecPoint = Misc::toVector3(-1557.292, 252.482, 114.767f);

				localCam = houseCam;
			}
			if (current_cell == 1) {
				//LocalCameraVec = toVector3(1774.191, 454.802, 112.283);
				LocalCameraVecPoint = Misc::toVector3(-1571.386, 245.765, 112.288);
				//CAM::RENDER_SCRIPT_CAMS(0, 1, 500, 1, 0, 0);

				localCam = outsideCam;
			}


		}


		if (menu_on == 2) {

			if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Back)) {

				AUDIO::PLAY_SOUND_FRONTEND("BACK", "HUD_SHOP_SOUNDSET", 1, 0);

				current_cell = 0;

				menu_on = 1;

			}



			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148, menuY + 0.25f, 0.2, 0.05f, 0, 60, 60, 60, 100);


			Misc::drawTextSmall("Bedroom", menuX + 0.021, menuY + 0.262f, 255, 255, 255, 255, 1, 0.4f, 0.4f);
			if (!strawRooms[0]) {
				Misc::drawText("$264", menuX + 0.021 + 0.135, menuY + 0.26f, 255, 255, 255, 255, 1, 0.55f, 0.55f);
			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}





			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148, menuY + 0.25f + 0.052, 0.2, 0.052f, 0, 60, 60, 60, 100);


			Misc::drawTextSmall("Bathroom", menuX + 0.024, menuY + 0.262f + 0.052, 255, 255, 255, 255, 1, 0.4f, 0.4f);

			if (!strawRooms[1]) {
				Misc::drawText("$180", menuX + 0.021 + 0.135, menuY + 0.26f + 0.052, 255, 255, 255, 255, 1, 0.55f, 0.55f);
			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f + 0.052, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}





			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148f, menuY + 0.25f + 0.104f, 0.2, 0.052f, 0, 60, 60, 60, 100);


			Misc::drawTextSmall("Dining Room", menuX + 0.032, menuY + 0.262f + 0.104f, 255, 255, 255, 255, 1, 0.4f, 0.4f);

			if (!strawRooms[2]) {
				Misc::drawText("$240", menuX + 0.021 + 0.135, menuY + 0.26f + 0.104f, 255, 255, 255, 255, 1, 0.55f, 0.55f);

			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f + 0.104f, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}



			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148f, menuY + 0.25f + 0.156f, 0.2, 0.052f, 0, 60, 60, 60, 100);

			Misc::drawTextSmall("Living room", menuX + 0.032, menuY + 0.262f + 0.156f, 255, 255, 255, 255, 1, 0.4f, 0.4f);

			if (!strawRooms[3]) {
				Misc::drawText("$189", menuX + 0.021 + 0.135, menuY + 0.26f + 0.156f, 255, 255, 255, 255, 1, 0.55f, 0.55f);

			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f + 0.156f, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}



			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148f, menuY + 0.25f + 0.208f, 0.2, 0.052f, 0, 60, 60, 60, 100);

			Misc::drawTextSmall("Weapon Locker", menuX + 0.04f, menuY + 0.262f + 0.208f, 255, 255, 255, 255, 1, 0.4f, 0.4f);

			if (!strawRooms[8]) {
				Misc::drawText("$165", menuX + 0.021f + 0.135f, menuY + 0.26f + 0.208f, 255, 255, 255, 255, 1, 0.55f, 0.55f);

			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f + 0.208f, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}






			Misc::drawSprite("generic_textures", "menu_bar", menuX - 0.0135, menuY + 0.88f, 0.2, 0.0025f, 0, 255, 255, 255, 120);



			Misc::drawSprite("generic_textures", "menu_bar", menuX - 0.0135, menuY + 0.459f + 0.05f, 0.2, 0.0025f, 0, 255, 255, 255, 120);


			Misc::drawSprite("generic_textures", "menu_bar", menuX - 0.0135, menuY + 0.25f, 0.2, 0.0025f, 0, 255, 255, 255, 120);


			float selectY = -0.013f + (0.0525f * menu_controls(4));
			Misc::drawSprite("menu_textures", "crafting_highlight_l", menuX + 0.294 - 0.315f, menuY + 0.123f + selectY + 0.142f, 0.0135, 0.05f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_r", menuX + 0.492 - 0.315f, menuY + 0.123f + selectY + 0.142f, 0.0135, 0.05f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_b", menuX + 0.3 - 0.315f, menuY + 0.1f + selectY + 0.142f, 0.2, 0.03f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_t", menuX + 0.3 - 0.315f, menuY + 0.165f + selectY + 0.142f, 0.2, 0.03f, 0, 255, 0, 0, 250);





			Misc::drawText("Upgrades", menuX + 0.085, menuY + 0.19f, 255, 255, 255, 255, 1, 0.45f, 0.45f);



			HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 0);
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 0);

			HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 1);
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 1);


			select_clock++;
			if (select_clock > 10) {


				if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Buy))
				{

					AUDIO::PLAY_SOUND_FRONTEND("PURCHASE", "Ledger_Sounds", 1, 0);



					//menu_on = 0;


					switch (current_cell) {
					case 0:
						strawRooms[0] = 1;
						BuyRoom("Houses/shepherds_bedroom.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(26400);
						break;
					case 1:
						strawRooms[1] = 1;
						BuyRoom("Houses/shepherds_bathroom.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(18000);
						break;
					case 2:
						strawRooms[2] = 1;
						BuyRoom("Houses/shepherds_dining.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(24000);
						break;
					case 3:
						strawRooms[3] = 1;
						BuyRoom("Houses/shepherds_livingroom.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(18900);
						break;
					case 4:
						strawRooms[8] = 1;
						BuyRoom("Houses/shepherds_gunlocker.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(16500);
						break;

					};
					select_clock = 0;
				}
			}



			if (current_cell == 0) {
				LocalCameraVecPoint = Misc::toVector3(-1549.406, 254.245, 114.799);
				if (!strawRooms[0]) {
					Room("Houses/shepherds_bedroom.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 26400) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}
				localCam = room1Cam;
			}
			if (current_cell == 1) {
				LocalCameraVecPoint = Misc::toVector3(-1546.114, 253.430, 114.905);
				if (!strawRooms[1]) {
					Room("Houses/shepherds_bathroom.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 18000) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}
				localCam = room2Cam;
			}
			if (current_cell == 2) {
				LocalCameraVecPoint = Misc::toVector3(-1552.207, 251.299, 114.799);
				if (!strawRooms[2]) {
					Room("Houses/shepherds_dining.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 24000) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}
				localCam = room3Cam;
			}
			if (current_cell == 3) {
				LocalCameraVecPoint = Misc::toVector3(-1554.278, 253.405, 114.799);
				if (!strawRooms[3]) {
					Room("Houses/shepherds_livingroom.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 18900) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}
				localCam = room4Cam;
			}
			if (current_cell == 4) {
				LocalCameraVecPoint = Misc::toVector3(-1549.841, 257.592, 114.6);
				if (!strawRooms[8]) {
					Room("Houses/shepherds_gunlocker.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 16500) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}
				localCam = room5Cam;
			}


		}


		if (menu_on == 3) {

			if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Back)) {
				

				AUDIO::PLAY_SOUND_FRONTEND("BACK", "HUD_SHOP_SOUNDSET", 1, 0);

				current_cell = 0;

				menu_on = 1;

			}

			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148, menuY + 0.25f, 0.2, 0.05f, 0, 60, 60, 60, 100);


			Misc::drawTextSmall("Hitching Post", menuX + 0.031, menuY + 0.262f, 255, 255, 255, 255, 1, 0.4f, 0.4f);
			if (!strawRooms[4]) {
				Misc::drawText("$65", menuX + 0.021 + 0.135, menuY + 0.26f, 255, 255, 255, 255, 1, 0.55f, 0.55f);
			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}





			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148, menuY + 0.25f + 0.052, 0.2, 0.052f, 0, 60, 60, 60, 100);


			Misc::drawTextSmall("Shooting Range", menuX + 0.036, menuY + 0.262f + 0.052, 255, 255, 255, 255, 1, 0.4f, 0.4f);

			if (!strawRooms[5]) {
				Misc::drawText("$125", menuX + 0.021 + 0.135, menuY + 0.26f + 0.052, 255, 255, 255, 255, 1, 0.55f, 0.55f);
			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f + 0.052, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}





			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148f, menuY + 0.25f + 0.104f, 0.2, 0.052f, 0, 60, 60, 60, 100);


			Misc::drawTextSmall("Trophies", menuX + 0.016, menuY + 0.262f + 0.104f, 255, 255, 255, 255, 1, 0.4f, 0.4f);

			if (!strawRooms[6]) {
				Misc::drawText("$570", menuX + 0.021 + 0.135, menuY + 0.26f + 0.104f, 255, 255, 255, 255, 1, 0.55f, 0.55f);

			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f + 0.104f, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}


			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148f, menuY + 0.25f + 0.156f, 0.2, 0.052f, 0, 60, 60, 60, 100);


			Misc::drawTextSmall("Campfire", menuX + 0.016, menuY + 0.262f + 0.156f, 255, 255, 255, 255, 1, 0.4f, 0.4f);

			if (!strawRooms[7]) {
				Misc::drawText("$42", menuX + 0.021 + 0.135, menuY + 0.26f + 0.156f, 255, 255, 255, 255, 1, 0.55f, 0.55f);

			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f + 0.156f, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}













			Misc::drawSprite("generic_textures", "menu_bar", menuX - 0.0135, menuY + 0.88f, 0.2, 0.0025f, 0, 255, 255, 255, 120);



			Misc::drawSprite("generic_textures", "menu_bar", menuX - 0.0135, menuY + 0.405f + 0.05f, 0.2, 0.0025f, 0, 255, 255, 255, 120);


			Misc::drawSprite("generic_textures", "menu_bar", menuX - 0.0135, menuY + 0.25f, 0.2, 0.0025f, 0, 255, 255, 255, 120);


			float selectY = -0.013f + (0.0525f * menu_controls(3));
			Misc::drawSprite("menu_textures", "crafting_highlight_l", menuX + 0.294 - 0.315f, menuY + 0.123f + selectY + 0.142f, 0.0135, 0.05f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_r", menuX + 0.492 - 0.315f, menuY + 0.123f + selectY + 0.142f, 0.0135, 0.05f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_b", menuX + 0.3 - 0.315f, menuY + 0.1f + selectY + 0.142f, 0.2, 0.03f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_t", menuX + 0.3 - 0.315f, menuY + 0.165f + selectY + 0.142f, 0.2, 0.03f, 0, 255, 0, 0, 250);





			Misc::drawText("Upgrades", menuX + 0.085, menuY + 0.19f, 255, 255, 255, 255, 1, 0.45f, 0.45f);



			HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 0);
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 0);

			HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 1);
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 1);


			select_clock++;
			if (select_clock > 10) {


				if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Buy))
				{
					
					AUDIO::PLAY_SOUND_FRONTEND("PURCHASE", "Ledger_Sounds", 1, 0);



					//menu_on = 0;


					switch (current_cell) {
					case 0:
						strawRooms[4] = 1;
						BuyRoom("Houses/shepherds_hitching_post.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(6500);
						break;
					case 1:
						strawRooms[5] = 1;
						BuyRoom("Houses/shepherds_outside.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(12500);
						break;
					case 2:
						strawRooms[6] = 1;
						BuyRoom("Houses/shepherds_trophies.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(57000);
						break;
					case 3:
						strawRooms[7] = 1;
						BuyRoom("Houses/shepherds_campfire.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(4200);
						break;



					};
					select_clock = 0;
				}

			}



			if (current_cell == 0) {
				LocalCameraVecPoint = Misc::toVector3(-1557.841, 247.331, 113.907f);

				localCam = outside1Cam;
				if (!strawRooms[4]) {
					Room("Houses/shepherds_hitching_post.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 6500) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}

			}
			if (current_cell == 1) {
				LocalCameraVecPoint = Misc::toVector3(-1565.440, 275.497, 115.548f);

				localCam = outside2Cam;
				if (!ridgeRooms[5]) {
					Room("Houses/shepherds_outside.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 12500) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}

			}
			if (current_cell == 2) {
				LocalCameraVecPoint = Misc::toVector3(-1554.110f, 254.728f, 114.799f);

				localCam = outside3Cam;
				if (!strawRooms[6]) {
					Room("Houses/shepherds_trophies.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 57000) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}

			}
			if (current_cell == 3) {
				LocalCameraVecPoint = Misc::toVector3(-1544.086f, 246.915f, 113.900f);

				localCam = outside4Cam;
				if (!strawRooms[7]) {
					Room("Houses/shepherds_campfire.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 4200) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}

			}







		}



		CAM::POINT_CAM_AT_COORD(localCam, LocalCameraVecPoint.x, LocalCameraVecPoint.y, LocalCameraVecPoint.z);
		CAM::RENDER_SCRIPT_CAMS(1, 1, 500, 1, 0, 0);
		CAM::SET_CAM_ACTIVE(localCam, 1);

	}

}


void Menu3() {

	if (menu_on > 0) {


		HUD::_UIPROMPT_SET_ENABLED(Prompt_Menu, 0);
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Menu, 0);

		HUD::HIDE_HUD_AND_RADAR_THIS_FRAME();

		HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 1);
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 1);

		HUD::_UIPROMPT_SET_ENABLED(Prompt_Back, 1);
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Back, 1);


		Misc::drawSprite("generic_textures", "inkroller_1a", menuX - 0.05f, menuY + 0.05, 0.27, 0.9f, 0, 0, 0, 0, 230);

		Misc::drawSprite("generic_textures", "menu_header_1a", menuX - 0.015, menuY + 0.08, 0.2, 0.1f, 0, 255, 255, 255, 255);
		Misc::drawText("Argil Rise", menuX + 0.09, menuY + 0.105, 255, 255, 255, 255, 1, 0.7f, 0.7f);




		if (menu_on == 1) {

			if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Back)) {
				

				AUDIO::PLAY_SOUND_FRONTEND("BACK", "HUD_SHOP_SOUNDSET", 1, 0);

				//TASK::CLEAR_PED_TASKS(player, 1, 1);

				if (menu_on > 1) {
					
				}
				else {
					//TASK::CLEAR_PED_TASKS(PLAYER::PLAYER_PED_ID(), 1, 1);

				}

				CAM::RENDER_SCRIPT_CAMS(0, 0, 500, 1, 0, 0);
				CAM::SET_CAM_ACTIVE(localCam, 0);

				vector<Object>::iterator objItr;
				for (objItr = tempObjects.begin(); objItr != tempObjects.end(); objItr++)
				{
					Object curr = *objItr;
					OBJECT::DELETE_OBJECT(&curr); //TEMP!!!!

				}

				ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), 1);

				current_cell = 0;
				if (menu_on > 1) {
					menu_on = 1;
				}
				else {
					menu_on = 0;
					TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID(), 1, 1);

					CAM::DESTROY_CAM(room1Cam, 1);
					CAM::DESTROY_CAM(room2Cam, 1);
					CAM::DESTROY_CAM(room3Cam, 1);
					CAM::DESTROY_CAM(room4Cam, 1);
					CAM::DESTROY_CAM(room5Cam, 1);
					CAM::DESTROY_CAM(room6Cam, 1);

					CAM::DESTROY_CAM(outside1Cam, 1);
					CAM::DESTROY_CAM(outside2Cam, 1);
					CAM::DESTROY_CAM(outside3Cam, 1);
					CAM::DESTROY_CAM(outside4Cam, 1);

					CAM::DESTROY_CAM(localCam, 1);

					CAM::DESTROY_CAM(houseCam, 1);
					CAM::DESTROY_CAM(outsideCam, 1);


				

				


				}


				
				return;
			}



			HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);

			Misc::drawTextSmall("Interior", menuX + 0.021, menuY + 0.26f, 255, 255, 255, 200, 1, 0.4f, 0.4f);
			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148, menuY + 0.25f, 0.2, 0.05f, 0, 60, 60, 60, 100);

			Misc::drawTextSmall("Outside", menuX + 0.02, menuY + 0.26f + 0.052, 255, 255, 255, 200, 1, 0.4f, 0.4f);
			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148, menuY + 0.25f + 0.052, 0.2, 0.052f, 0, 60, 60, 60, 100);

			Misc::drawSprite("generic_textures", "menu_bar", menuX - 0.0135, menuY + 0.35f, 0.2, 0.0025f, 0, 255, 255, 255, 120);







			float selectY = -0.013f + (0.0525f * menu_controls(1));
			Misc::drawSprite("menu_textures", "crafting_highlight_l", menuX + 0.294 - 0.315f, menuY + 0.123f + selectY + 0.142f, 0.0135, 0.05f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_r", menuX + 0.492 - 0.315f, menuY + 0.123f + selectY + 0.142f, 0.0135, 0.05f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_b", menuX + 0.3 - 0.315f, menuY + 0.1f + selectY + 0.142f, 0.2, 0.03f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_t", menuX + 0.3 - 0.315f, menuY + 0.165f + selectY + 0.142f, 0.2, 0.03f, 0, 255, 0, 0, 250);






			Misc::drawText("Upgrades", menuX + 0.085, menuY + 0.19f, 255, 255, 255, 255, 1, 0.45f, 0.45f);


			Misc::drawSprite("generic_textures", "menu_bar", menuX - 0.0135, menuY + 0.88f, 0.2, 0.0025f, 0, 255, 255, 255, 120);







			select_clock++;
			if (select_clock > 10) {


				if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Select))
				{

					AUDIO::PLAY_SOUND_FRONTEND("INFO", "HUD_SHOP_SOUNDSET", 1, 0);

					//menu_on = 0;
					menu_on = 0;

					switch (current_cell) {
					case 0:
						menu_on = 2;

						current_cell = 0;

						CAM::DESTROY_CAM(room1Cam, 1);
						CAM::DESTROY_CAM(room2Cam, 1);
						CAM::DESTROY_CAM(room3Cam, 1);
						CAM::DESTROY_CAM(room4Cam, 1);
						CAM::DESTROY_CAM(room5Cam, 1);
						CAM::DESTROY_CAM(room6Cam, 1);

						room1Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1454.446f, -1573.804f, 73.016f, 0, 0, 0, 60, 1, 2);
						room2Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1455.671f, -1574.558f, 73.016f, 0, 0, 0, 60, 1, 2);
						room3Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1455.477f, -1582.329f, 73.016f, 0, 0, 0, 60, 1, 2);
						room4Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1456.379f, -1584.558f, 73.016f, 0, 0, 0, 60, 1, 2);
						room5Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1455.865f, -1580.878f, 72.016f, 0, 0, 0, 60, 1, 2);
						room6Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1455.653f, -1581.525f, 72.016f, 0, 0, 0, 60, 1, 2);



						break;
					case 1:
						menu_on = 3;

						current_cell = 0;

						CAM::DESTROY_CAM(outside1Cam, 1);
						CAM::DESTROY_CAM(outside2Cam, 1);
						CAM::DESTROY_CAM(outside3Cam, 1);
						CAM::DESTROY_CAM(outside4Cam, 1);

						outside1Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1444.371f, -1578.666f, 73.122, 0, 0, 0, 60, 1, 2);
						outside2Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1489.521f, -1588.617f, 72.960f, 0, 0, 0, 60, 1, 2);
						outside3Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1459.713f, -1587.797f, 71.841f, 0, 0, 0, 60, 1, 2);
						outside4Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1399.080f, -1578.822f, 67.398f, 0, 0, 0, 60, 1, 2);


						break;



					};
					select_clock = 0;
				}



			}



			if (current_cell == 0) {
				//LocalCameraVec = toVector3(1774.191, 456.f, 114.f);
				LocalCameraVecPoint = Misc::toVector3(1460.475, -1581.111, 71.843f);

				localCam = houseCam;
			}
			if (current_cell == 1) {
				//LocalCameraVec = toVector3(1774.191, 454.802, 112.283);
				LocalCameraVecPoint = Misc::toVector3(1462.813, -1604.591, 70.914);
				//CAM::RENDER_SCRIPT_CAMS(0, 1, 500, 1, 0, 0);

				localCam = outsideCam;
			}


		}


		if (menu_on == 2) {

			if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Back)) {
				

				AUDIO::PLAY_SOUND_FRONTEND("BACK", "HUD_SHOP_SOUNDSET", 1, 0);

				current_cell = 0;

				menu_on = 1;

			}



			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148, menuY + 0.25f, 0.2, 0.05f, 0, 60, 60, 60, 100);


			Misc::drawTextSmall("Bedroom", menuX + 0.021, menuY + 0.262f, 255, 255, 255, 255, 1, 0.4f, 0.4f);
			if (!argilRooms[0]) {
				Misc::drawText("$219", menuX + 0.021 + 0.135, menuY + 0.26f, 255, 255, 255, 255, 1, 0.55f, 0.55f);
			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}





			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148, menuY + 0.25f + 0.052, 0.2, 0.052f, 0, 60, 60, 60, 100);


			Misc::drawTextSmall("Bathroom", menuX + 0.024, menuY + 0.262f + 0.052, 255, 255, 255, 255, 1, 0.4f, 0.4f);

			if (!argilRooms[1]) {
				Misc::drawText("$236", menuX + 0.021 + 0.135, menuY + 0.26f + 0.052, 255, 255, 255, 255, 1, 0.55f, 0.55f);
			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f + 0.052, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}





			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148f, menuY + 0.25f + 0.104f, 0.2, 0.052f, 0, 60, 60, 60, 100);


			Misc::drawTextSmall("Patriot Bundle", menuX + 0.038, menuY + 0.262f + 0.104f, 255, 255, 255, 255, 1, 0.4f, 0.4f);

			if (!argilRooms[2]) {
				Misc::drawText("$40", menuX + 0.021 + 0.135, menuY + 0.26f + 0.104f, 255, 255, 255, 255, 1, 0.55f, 0.55f);

			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f + 0.104f, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}



			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148f, menuY + 0.25f + 0.156f, 0.2, 0.052f, 0, 60, 60, 60, 100);

			Misc::drawTextSmall("Living room", menuX + 0.032, menuY + 0.262f + 0.156f, 255, 255, 255, 255, 1, 0.4f, 0.4f);

			if (!argilRooms[3]) {
				Misc::drawText("$277", menuX + 0.021 + 0.135, menuY + 0.26f + 0.156f, 255, 255, 255, 255, 1, 0.55f, 0.55f);

			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f + 0.156f, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}


			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148f, menuY + 0.25f + 0.208f, 0.2, 0.052f, 0, 60, 60, 60, 100);

			Misc::drawTextSmall("Trophies", menuX + 0.021, menuY + 0.262f + 0.208f, 255, 255, 255, 255, 1, 0.4f, 0.4f);

			if (!argilRooms[4]) {
				Misc::drawText("$543", menuX + 0.021 + 0.135, menuY + 0.26f + 0.208f, 255, 255, 255, 255, 1, 0.55f, 0.55f);

			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f + 0.208f, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}


			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148f, menuY + 0.25f + 0.26f, 0.2, 0.052f, 0, 60, 60, 60, 100);

			Misc::drawTextSmall("Weapon Locker", menuX + 0.04, menuY + 0.262f + 0.26f, 255, 255, 255, 255, 1, 0.4f, 0.4f);

			if (!argilRooms[9]) {
				Misc::drawText("$165", menuX + 0.021 + 0.135, menuY + 0.26f + 0.26f, 255, 255, 255, 255, 1, 0.55f, 0.55f);

			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f + 0.26f, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}





			Misc::drawSprite("generic_textures", "menu_bar", menuX - 0.0135, menuY + 0.88f, 0.2, 0.0025f, 0, 255, 255, 255, 120);



			Misc::drawSprite("generic_textures", "menu_bar", menuX - 0.0135, menuY + 0.405f + 0.156f, 0.2, 0.0025f, 0, 255, 255, 255, 120);


			Misc::drawSprite("generic_textures", "menu_bar", menuX - 0.0135, menuY + 0.25f, 0.2, 0.0025f, 0, 255, 255, 255, 120);


			float selectY = -0.013f + (0.0525f * menu_controls(5));
			Misc::drawSprite("menu_textures", "crafting_highlight_l", menuX + 0.294 - 0.315f, menuY + 0.123f + selectY + 0.142f, 0.0135, 0.05f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_r", menuX + 0.492 - 0.315f, menuY + 0.123f + selectY + 0.142f, 0.0135, 0.05f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_b", menuX + 0.3 - 0.315f, menuY + 0.1f + selectY + 0.142f, 0.2, 0.03f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_t", menuX + 0.3 - 0.315f, menuY + 0.165f + selectY + 0.142f, 0.2, 0.03f, 0, 255, 0, 0, 250);





			Misc::drawText("Upgrades", menuX + 0.085, menuY + 0.19f, 255, 255, 255, 255, 1, 0.45f, 0.45f);



			HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 0);
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 0);

			HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 1);
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 1);


			select_clock++;
			if (select_clock > 10) {


				if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Buy))
				{
					

					AUDIO::PLAY_SOUND_FRONTEND("PURCHASE", "Ledger_Sounds", 1, 0);



					//menu_on = 0;


					switch (current_cell) {
					case 0:
						argilRooms[0] = 1;
						BuyRoom("Houses/argil_bedroom.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(21900);
						break;
					case 1:
						argilRooms[1] = 1;
						BuyRoom("Houses/argil_bathroom.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(23600);
						break;
					case 2:
						argilRooms[2] = 1;
						BuyRoom("Houses/argil_murica.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(4000);
						break;
					case 3:
						argilRooms[3] = 1;
						BuyRoom("Houses/argil_livingroom.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(27700);
						break;
					case 4:
						argilRooms[4] = 1;
						BuyRoom("Houses/argil_hunters.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(54300);
						break;
					case 5:
						argilRooms[9] = 1;
						BuyRoom("Houses/argil_gunlocker.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(16500);
						break;


					};
					select_clock = 0;
				}
			}



			if (current_cell == 0) {
				LocalCameraVecPoint = Misc::toVector3(1451.859, -1574.234, 72.016);
				if (!argilRooms[0]) {
					Room("Houses/argil_bedroom.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 21900) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}
				localCam = room1Cam;
			}
			if (current_cell == 1) {
				LocalCameraVecPoint = Misc::toVector3(1456.560, -1576.646, 72.016);
				if (!argilRooms[1]) {
					Room("Houses/argil_bathroom.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 23600) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}
				localCam = room2Cam;
			}
			if (current_cell == 2) {
				LocalCameraVecPoint = Misc::toVector3(1456.749, -1582.998, 73.139);
				if (!argilRooms[2]) {
					Room("Houses/argil_murica.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 4000) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}
				localCam = room3Cam;
			}
			if (current_cell == 3) {
				LocalCameraVecPoint = Misc::toVector3(1454.807, -1579.635, 72.016);
				if (!argilRooms[3]) {
					Room("Houses/argil_livingroom.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 27700) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}
				localCam = room4Cam;
			}
			if (current_cell == 4) {
				LocalCameraVecPoint = Misc::toVector3(1452.519, -1581.412, 73.516);
				if (!argilRooms[4]) {
					Room("Houses/argil_hunters.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 54300) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}
				localCam = room4Cam;
			}
			if (current_cell == 5) {
				LocalCameraVecPoint = Misc::toVector3(1455.285, -1583.419, 72.0);
				if (!argilRooms[9]) {
					Room("Houses/argil_gunlocker.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 16500) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}
				localCam = room5Cam;
			}


		}


		if (menu_on == 3) {

			if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Back)) {
				

				AUDIO::PLAY_SOUND_FRONTEND("BACK", "HUD_SHOP_SOUNDSET", 1, 0);

				current_cell = 0;

				menu_on = 1;

			}

			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148, menuY + 0.25f, 0.2, 0.05f, 0, 60, 60, 60, 100);


			Misc::drawTextSmall("Hitching Post", menuX + 0.031, menuY + 0.262f, 255, 255, 255, 255, 1, 0.4f, 0.4f);
			if (!argilRooms[5]) {
				Misc::drawText("$65", menuX + 0.021 + 0.135, menuY + 0.26f, 255, 255, 255, 255, 1, 0.55f, 0.55f);
			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}





			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148, menuY + 0.25f + 0.052, 0.2, 0.052f, 0, 60, 60, 60, 100);


			Misc::drawTextSmall("Campfire", menuX + 0.016, menuY + 0.262f + 0.052, 255, 255, 255, 255, 1, 0.4f, 0.4f);

			if (!argilRooms[6]) {
				Misc::drawText("$43", menuX + 0.021 + 0.135, menuY + 0.26f + 0.052, 255, 255, 255, 255, 1, 0.55f, 0.55f);
			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f + 0.052, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}





			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148f, menuY + 0.25f + 0.104f, 0.2, 0.052f, 0, 60, 60, 60, 100);


			Misc::drawTextSmall("Outdoorsman bundle", menuX + 0.051, menuY + 0.262f + 0.104f, 255, 255, 255, 255, 1, 0.4f, 0.4f);

			if (!argilRooms[7]) {
				Misc::drawText("$120", menuX + 0.021 + 0.135, menuY + 0.26f + 0.104f, 255, 255, 255, 255, 1, 0.55f, 0.55f);

			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f + 0.104f, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}



			Misc::drawSprite("generic_textures", "selection_box_bg_1c", menuX - 0.0148f, menuY + 0.25f + 0.156f, 0.2, 0.052f, 0, 60, 60, 60, 100);


			Misc::drawTextSmall("Shooting Range", menuX + 0.035, menuY + 0.262f + 0.156f, 255, 255, 255, 255, 1, 0.4f, 0.4f);

			if (!argilRooms[8]) {
				Misc::drawText("$142", menuX + 0.021 + 0.135, menuY + 0.26f + 0.156f, 255, 255, 255, 255, 1, 0.55f, 0.55f);

			}
			else {
				Misc::drawSprite("generic_textures", "tick", menuX + 0.021 + 0.133, menuY + 0.26f + 0.156f, 0.02, 0.03f, 0, 255, 255, 255, 255);

			}















			Misc::drawSprite("generic_textures", "menu_bar", menuX - 0.0135, menuY + 0.88f, 0.2, 0.0025f, 0, 255, 255, 255, 120);



			Misc::drawSprite("generic_textures", "menu_bar", menuX - 0.0135, menuY + 0.405f + 0.05f, 0.2, 0.0025f, 0, 255, 255, 255, 120);


			Misc::drawSprite("generic_textures", "menu_bar", menuX - 0.0135, menuY + 0.25f, 0.2, 0.0025f, 0, 255, 255, 255, 120);


			float selectY = -0.013f + (0.0525f * menu_controls(3));
			Misc::drawSprite("menu_textures", "crafting_highlight_l", menuX + 0.294 - 0.315f, menuY + 0.123f + selectY + 0.142f, 0.0135, 0.05f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_r", menuX + 0.492 - 0.315f, menuY + 0.123f + selectY + 0.142f, 0.0135, 0.05f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_b", menuX + 0.3 - 0.315f, menuY + 0.1f + selectY + 0.142f, 0.2, 0.03f, 0, 255, 0, 0, 250);
			Misc::drawSprite("menu_textures", "crafting_highlight_t", menuX + 0.3 - 0.315f, menuY + 0.165f + selectY + 0.142f, 0.2, 0.03f, 0, 255, 0, 0, 250);





			Misc::drawText("Upgrades", menuX + 0.085, menuY + 0.19f, 255, 255, 255, 255, 1, 0.45f, 0.45f);



			HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 0);
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 0);

			HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 1);
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 1);


			select_clock++;
			if (select_clock > 10) {


				if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Buy))
				{
					

					AUDIO::PLAY_SOUND_FRONTEND("PURCHASE", "Ledger_Sounds", 1, 0);



					//menu_on = 0;


					switch (current_cell) {
					case 0:
						argilRooms[5] = 1;
						BuyRoom("Houses/argil_hitching_post.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(6500);
						break;
					case 1:
						argilRooms[6] = 1;
						BuyRoom("Houses/argil_campfire.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(4300);
						break;
					case 2:
						argilRooms[7] = 1;
						BuyRoom("Houses/argil_outdoorsman.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(12000);
						break;
					case 3:
						argilRooms[8] = 1;
						BuyRoom("Houses/argil_shootingrange.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(14200);
						break;






					};
					select_clock = 0;
				}



			}



			if (current_cell == 0) {
				LocalCameraVecPoint = Misc::toVector3(1447.755, -1578.523, 71.843f);
				/*
				CAM::DESTROY_CAM(localCam, 1);
				localCam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1444.371f, -1578.666f, 73.122, 0, 0, 0, 60, 1, 2);
				*/
				localCam = outside1Cam;

				if (!argilRooms[5]) {
					Room("Houses/argil_hitching_post.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 6500) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}

			}
			if (current_cell == 1) {
				LocalCameraVecPoint = Misc::toVector3(1492.617, -1590.396, 72.963f);

				localCam = outside2Cam;


				if (!argilRooms[6]) {
					Room("Houses/argil_campfire.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 4300) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}

			}
			if (current_cell == 2) {
				LocalCameraVecPoint = Misc::toVector3(1456.739f, -1589.782f, 71.821f);

				localCam = outside3Cam;


				if (!argilRooms[7]) {
					Room("Houses/argil_outdoorsman.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 12000) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}

			}

			if (current_cell == 3) {
				LocalCameraVecPoint = Misc::toVector3(1403.696f, -1569.534f, 68.754f);

				localCam = outside4Cam;


				if (!argilRooms[8]) {
					Room("Houses/argil_shootingrange.xml", tempObjects);

					if (MONEY::_MONEY_GET_CASH_BALANCE() <= 14200) {
						HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					}

				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);
				}

			}







		}



		CAM::POINT_CAM_AT_COORD(localCam, LocalCameraVecPoint.x, LocalCameraVecPoint.y, LocalCameraVecPoint.z);
		CAM::RENDER_SCRIPT_CAMS(1, 1, 500, 1, 0, 0);
		CAM::SET_CAM_ACTIVE(localCam, 1);

	}

}



void loadRidgeView() {


	if (ridgeRooms[0]) {
		BuyRoom("Houses/ridge_bedroom.xml", mainObjects);
	}

	if (ridgeRooms[1]) {
		BuyRoom("Houses/ridge_study.xml", mainObjects);
	}

	if (ridgeRooms[2]) {
		BuyRoom("Houses/ridge_livingroom.xml", mainObjects);
	}

	if (ridgeRooms[3]) {
		BuyRoom("Houses/ridge_hitchingpost.xml", mainObjects);
	}

	if (ridgeRooms[4]) {
		BuyRoom("Houses/ridge_campfire.xml", mainObjects);
	}

	if (ridgeRooms[5]) {
		BuyRoom("Houses/ridge_farmers.xml", mainObjects);
	}

	if (ridgeRooms[6]) {
		BuyRoom("Houses/ridge_nature.xml", mainObjects);
	}

	if (ridgeRooms[7]) {
		BuyRoom("Houses/ridge_outdoorsman.xml", mainObjects);
	}
	if (ridgeRooms[8]) {
		BuyRoom("Houses/ridge_gunlocker.xml", mainObjects);
	}
}


void loadShepherdsView() {


	if (strawRooms[0]) {
		BuyRoom("Houses/shepherds_bedroom.xml", mainObjects);
	}

	if (strawRooms[1]) {
		BuyRoom("Houses/shepherds_bathroom.xml", mainObjects);
	}

	if (strawRooms[2]) {
		BuyRoom("Houses/shepherds_dining.xml", mainObjects);
	}

	if (strawRooms[3]) {
		BuyRoom("Houses/shepherds_livingroom.xml", mainObjects);
	}

	if (strawRooms[4]) {
		BuyRoom("Houses/shepherds_hitching_post.xml", mainObjects);
	}

	if (strawRooms[5]) {
		BuyRoom("Houses/shepherds_outside.xml", mainObjects);
	}

	if (strawRooms[6]) {
		BuyRoom("Houses/shepherds_trophies.xml", mainObjects);
	}



}


void loadArgilView() {


	if (argilRooms[0]) {
		BuyRoom("Houses/argil_bedroom.xml", mainObjects);
	}

	if (argilRooms[1]) {
		BuyRoom("Houses/argil_bathroom.xml", mainObjects);
	}

	if (argilRooms[2]) {
		BuyRoom("Houses/argil_murica.xml", mainObjects);
	}

	if (argilRooms[3]) {
		BuyRoom("Houses/argil_livingroom.xml", mainObjects);
	}

	if (argilRooms[4]) {
		BuyRoom("Houses/argil_hunters.xml", mainObjects);
	}

	if (argilRooms[5]) {
		BuyRoom("Houses/argil_hitching_post.xml", mainObjects);
	}

	if (argilRooms[6]) {
		BuyRoom("Houses/argil_campfire.xml", mainObjects);
	}

	if (argilRooms[7]) {
		BuyRoom("Houses/argil_outdoorsman.xml", mainObjects);
	}

	if (argilRooms[8]) {
		BuyRoom("Houses/argil_shootingrange.xml", mainObjects);
	}



}

//disable movement
//PED::SET_PED_RESET_FLAG(func_263(uParam0), 258, true);
//PAD::DISABLE_CONTROL_ACTION(0, -668070958, false);
//PAD::DISABLE_CONTROL_ACTION(0, 1250966545, false);
//PAD::DISABLE_CONTROL_ACTION(0, -2131587435, false);


int hold_mode_timer;

Entity weaponEnt;




Vector3 ridgeLocker = Misc::toVector3(1785.533f, 460.536f, 113.040f);
Vector3 strawLocker = Misc::toVector3(-1549.841, 257.592, 114.6);
Vector3 argilsLocker = Misc::toVector3(1455.285, -1583.419, 72.0);
Blip WeaponLockerBlip[3];

Vector3 lockerCoords[3] = { ridgeLocker, strawLocker, argilsLocker };


Vector3 ridgeOutfitters = Misc::toVector3(1779.206, 459.615, 111.6);
Vector3 strawOutfitters = Misc::toVector3(-1558.191, 254.843, 113.0);
Vector3 argilsOutfitters = Misc::toVector3(1461.855f, -1577.275f, 71.843f);
Blip ridgeOutfittersBlips[3];


Vector3 outfittersCoords[3] = { ridgeOutfitters, strawOutfitters, argilsOutfitters };



Vector3 ridgeBed = Misc::toVector3(1783.625f, 466.568f, 112.971f);
Vector3 strawBed = Misc::toVector3(-1547.801f, 257.991f, 114.80f);
Vector3 argilsBed = Misc::toVector3(1453.091f, -1573.048f, 71.843f);
Blip bedBlips[3];


Vector3 bedCoords[3] = { ridgeBed, strawBed, argilsBed };



void bedBlip(Vector3 playerPos) {

	for (int i = 0; i < 3; i++) {
		if (distanceBetween(playerPos, outfittersCoords[i]) < 30.f && INTERIOR::IS_INTERIOR_SCENE()) { //TODO add interior check

			if (!MAP::DOES_BLIP_EXIST(bedBlips[i])) {
				bedBlips[i] = MAP::_BLIP_ADD_FOR_COORD(0x63351D54, bedCoords[i].x, bedCoords[i].y, bedCoords[i].z);
				//MAP::BLIP_ADD_MODIFIER(WeaponLockerBlip, MISC::GET_HASH_KEY("BLIP_MODIFIER_RADAR_EDGE_NEVER"));
				MAP::SET_BLIP_SPRITE(bedBlips[i], MISC::GET_HASH_KEY("blip_region_caravan"), false);
				MAP::_SET_BLIP_NAME_FROM_PLAYER_STRING(bedBlips[i], (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Bed"));
			}

		}
		else {
			Misc::removeBlipSafe(bedBlips[i]);
		}

	}

}

void weaponLocker(Vector3 playerPos) {
	for (int i = 0; i < 3; i++) {
		if (distanceBetween(playerPos, outfittersCoords[i]) < 30.f && INTERIOR::IS_INTERIOR_SCENE()) {

			if (!MAP::DOES_BLIP_EXIST(WeaponLockerBlip[i])) {
				if ((i == 0 && ridgeRooms[8]) || (i == 1 && strawRooms[8]) || (i == 2 && argilRooms[9])) {
					WeaponLockerBlip[i] = MAP::_BLIP_ADD_FOR_COORD(0x63351D54, lockerCoords[i].x, lockerCoords[i].y, lockerCoords[i].z);
					//MAP::BLIP_ADD_MODIFIER(WeaponLockerBlip, MISC::GET_HASH_KEY("BLIP_MODIFIER_RADAR_EDGE_NEVER"));
					MAP::SET_BLIP_SPRITE(WeaponLockerBlip[i], MISC::GET_HASH_KEY("blip_supplies_ammo"), false);
					MAP::_SET_BLIP_NAME_FROM_PLAYER_STRING(WeaponLockerBlip[i], (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Weapon Locker"));
				}

			}

		}
		else {
			Misc::removeBlipSafe(WeaponLockerBlip[i]);
		}


	}

	//<Object Hash="-1130235754" Position_x="-1550.3407" Position_y="258.15909" Position_z="114.2109" Rotation_x="-4" Rotation_y="0" Rotation_z="21.9998" TextureVariation="0" Collision="true" Dynamic="false" LOD="15" BlipHash="0" BlipType="0"/>
	if ((distanceBetween(playerPos, Misc::toVector3(1785.533f, 460.536f, 113.040f)) < 1.5f && ridgeRooms[8])
		|| (distanceBetween(playerPos, Misc::toVector3(-1551.093, 257.612, 114.6)) < 1.5f && strawRooms[8])
		|| (distanceBetween(playerPos, Misc::toVector3(1455.285, -1583.419, 72.0)) < 1.5f && argilRooms[9])) {
		HUD::_UIPROMPT_SET_GROUP(Prompt_Locker, -2019190071, 0);

		HUD::_UIPROMPT_SET_ACTIVE_GROUP_THIS_FRAME(-2019190071, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Wardrobe"), 1, 0, 0, 0);

		HUD::_UIPROMPT_SET_ENABLED(Prompt_Locker, 1);
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Locker, 1);

	}




	hold_mode_timer++;
	if (hold_mode_timer > 60) {
		if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Locker)) {
			char* scriptName = "weapon_locker";
			if (!SCRIPTS::DOES_SCRIPT_EXIST(scriptName))
			{
				Misc::showSubtitle("script does not exist");
			}
			else
			{
				while (!SCRIPTS::HAS_SCRIPT_LOADED(scriptName))
				{
					SCRIPTS::REQUEST_SCRIPT(scriptName);
					WAIT(15);
				}

				SCRIPTS::START_NEW_SCRIPT(scriptName, 1024);
			}
			hold_mode_timer = 0;
		}
	}
	//HUD::_UIPROMPT_SET_GROUP(Prompt_Locker, 1754796591, 1);
	//HUD::_UIPROMPT_SET_ACTIVE_GROUP_THIS_FRAME(1754796591, 0, 0, 0, 0, 1754796591);
	//HUD::_UIPROMPT_SET_AMBIENT_GROUP_THIS_FRAME(weaponEnt, 1.f, 1, 1, -484761727, "WARDROBE", 2);
	//ENTITY::IS_ENTITY_IN_VOLUME



}




void main()
{		


	initialize();




	Misc::createProp(0x6281781F, Misc::toVector3(1461.291, -1578.447, 70.8), 60, 1, 1);
	Misc::createProp(0x5D452073, Misc::toVector3(1461.72, -1578.68, 71.614), Misc::toVector3(270, 0, 60), 60, 1, 1);

	
	Misc::createProp(0xE546FB46, Misc::toVector3(1460.9, -1578.68, 71.58), Misc::toVector3(0, 0, 30), 60, 1, 1);
	//Misc::createProp(0xC503C036, Misc::toVector3(1461.72, -1578.68, 71.614), 60, 1, 1);


	//1779.806, 457.615, 111.6
	Misc::createProp(0x6281781F, Misc::toVector3(1779.206, 459.615, 111.6), 285, 1, 1);
	Misc::createProp(0x5D452073, Misc::toVector3(1778.8, 459.471, 112.42), Misc::toVector3(270, 0, -75), 285, 1, 1);


	
	Misc::createProp(0x6281781F, Misc::toVector3(-1558.191, 254.843, 113.0), 292, 1, 1);
	Misc::createProp(0x5D452073, Misc::toVector3(-1558.60, 254.643, 113.82), Misc::toVector3(270, 0, -70), 285, 1, 1);


	

	bool room_bought = 0;


	//HUD::_UIPROMPT_SET_GROUP(Prompt_Ledger, -2019190071, 0);

	//HUD::_UIPROMPT_SET_ACTIVE_GROUP_THIS_FRAME(-2019190071, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Beechers Hope"), 1, 0, 0, 0);




	int roomBlip;
	int houseBlip;

	Load();

	int save_timer = 0;








	//weaponEnt = createProp(1784348138, toVector3(1784.7306, 460.11401, 112.0402), toVector3(0, 0, 0), 0, 1, 1);








	//bool once = 0;

	localCam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 0, 0, 0, 0, 0, 0, 60, 1, 2);

	houseCam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1774.191, 457.802, 113.f, 0, 0, 0, 60, 1, 2);
	outsideCam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1774.191, 454.802, 112.283, 0, 0, 0, 60, 1, 2);

	//houseCam2 = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", -1561.542, 243.617, 115.574f, 0, 0, 0, 60, 1, 2);
	//outsideCam2 = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", -1561.542, 243.617, 113.574f, 0, 0, 0, 60, 1, 2);

	//houseCam3 = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1468.489f, -1579.170f, 72.080f, 0, 0, 0, 60, 1, 2);
	//outsideCam3 = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1460.451f, -1589.812f, 71.837f, 0, 0, 0, 60, 1, 2);







	room1Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1788.470, 465.166, 114.072, 0, 0, 0, 60, 1, 2);
	room2Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1784.488, 461.218, 113.984, 0, 0, 0, 60, 1, 2);
	room3Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1780.750f, 457.612f, 114.019f, 0, 0, 0, 60, 1, 2);

	//gun locker



	outside1Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1773.002, 460.635, 114.404, 0, 0, 0, 60, 1, 2);
	outside2Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1782.116, 448.621, 114.349, 0, 0, 0, 60, 1, 2);
	outside3Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1752.424f, 443.926f, 114.179f, 0, 0, 0, 60, 1, 2);

	outside4Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1778.572, 526.340, 108.713, 0, 0, 0, 60, 1, 2);
	outside5Cam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1780.441f, 451.111f, 114.179f, 0, 0, 0, 60, 1, 2);




	


	bool init = 0;



	int arthur_mode = GetPrivateProfileInt("MISC", "ARTHUR_MODE", 0, ".\\Houses.ini");
	int epilogue = 0;
	if (PED::IS_PED_MODEL(PLAYER::PLAYER_PED_ID(), MISC::GET_HASH_KEY("Player_Three"))) {
		epilogue = 1;
	}


	if (arthur_mode || epilogue) {
		if (Houses[1]) {
			BuyRoom("Houses/ridge_base.xml", mainObjects);
		}

		if (Houses[2]) {
			BuyRoom("Houses/shepherds_base.xml", mainObjects);
		}

		if (Houses[7]) {
			BuyRoom("Houses/argil_base.xml", mainObjects);
		}





		loadRidgeView();

		loadShepherdsView();

		loadArgilView();
	}

	int current_cash = MONEY::_MONEY_GET_CASH_BALANCE();
	int next_cash = MONEY::_MONEY_GET_CASH_BALANCE();
	int cash_timer = MISC::GET_GAME_TIMER() + 10000;

	Vector3 roomBeds[6] = { Misc::toVector3(-326.615, 766.180, 121.636), Misc::toVector3(-328.489, 772.667, 121.634),  Misc::toVector3(-326.399, 758.961, 117.436), Misc::toVector3(-326.894, 766.255, 117.434), Misc::toVector3(-1819.358, -367.668, 166.507), Misc::toVector3(1332.767, -1371.250, 80.490) };
	Vector3 roomWardrobes[6] = { Misc::toVector3(-327.270, 764.147, 121.633), Misc::toVector3(0, 0, 0), Misc::toVector3(-323.196, 759.662, 117.436), Misc::toVector3(-325.125, 766.450, 117.434), Misc::toVector3(-1817.158, -368.672, 166.506), Misc::toVector3(1330.865, -1373.489, 80.490) };
	Vector3 roomChairs[6] = { Misc::toVector3(-327.270, 764.147, 121.633), Misc::toVector3(0, 0, 0), Misc::toVector3(0, 0, 0), 0, 0 };

	while (true)
	{
		Ped player = PLAYER::PLAYER_PED_ID();
		Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, false);
		Ped playerHorse = PLAYER::_GET_SADDLE_HORSE_FOR_PLAYER(0);


		Toasts::updateUI();


		HUD::_UIPROMPT_SET_VISIBLE(PromptRoom, 0);
		HUD::_UIPROMPT_SET_ENABLED(PromptRoom, 0);

		HUD::_UIPROMPT_SET_ENABLED(Prompt_Select, 0);
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Select, 0);

		HUD::_UIPROMPT_SET_ENABLED(Prompt_Back, 0);
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Back, 0);

		HUD::_UIPROMPT_SET_ENABLED(Prompt_Buy, 0);
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Buy, 0);


		HUD::_UIPROMPT_SET_ENABLED(Prompt_Locker, 0);
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Locker, 0);


		if (INVENTORY::_0xE787F05DFC977BDE(INVENTORY::_INVENTORY_GET_PED_INVENTORY_ID(player), MISC::GET_HASH_KEY("DOCUMENT_MACFARLANE_RANCH_DEED"), 0)) {
			Misc::showSubtitle("1");
		}

		save_timer++;
		if (save_timer > 100) {

		
			Save();

			save_timer = 0;


			CAM::SET_CAM_ACTIVE(localCam, 0);
			CAM::SET_CAM_ACTIVE(houseCam, 0);
			CAM::SET_CAM_ACTIVE(outsideCam, 0);

			CAM::SET_CAM_ACTIVE(room1Cam, 0);
			CAM::SET_CAM_ACTIVE(room2Cam, 0);
			CAM::SET_CAM_ACTIVE(room3Cam, 0);

			CAM::SET_CAM_ACTIVE(outside1Cam, 0);
			CAM::SET_CAM_ACTIVE(outside2Cam, 0);
			CAM::SET_CAM_ACTIVE(outside3Cam, 0);
			CAM::SET_CAM_ACTIVE(outside4Cam, 0);
			CAM::SET_CAM_ACTIVE(outside5Cam, 0);
			
			

			if (arthur_mode) {
				STREAMING::_REMOVE_IMAP(651621232);
				STREAMING::_REMOVE_IMAP(979670262);
				STREAMING::_REMOVE_IMAP(418666411);
				STREAMING::_REMOVE_IMAP(-165202905);
				STREAMING::_REMOVE_IMAP(-1327148782);
				STREAMING::_REMOVE_IMAP(-1965378386);
				STREAMING::_REMOVE_IMAP(894787561);
				STREAMING::_REMOVE_IMAP(-1079295176);



			}
		}

		if (!STREAMING::_IS_IMAP_ACTIVE(-1405375965)) {
			STREAMING::_REQUEST_IMAP(-1405375965);
		}

		if (!STREAMING::_IS_IMAP_ACTIVE(-1386423483)) {
			STREAMING::_REQUEST_IMAP(-1386423483);
		}

		if (!STREAMING::_IS_IMAP_ACTIVE(-1276109918)) {
			STREAMING::_REQUEST_IMAP(-1276109918);
		}

		if (!STREAMING::_IS_IMAP_ACTIVE(1133172356)) {
			STREAMING::_REQUEST_IMAP(1133172356);
		}

		if (!STREAMING::_IS_IMAP_ACTIVE(-559257162)) {
			STREAMING::_REQUEST_IMAP(-559257162);
		}

		if (!STREAMING::_IS_IMAP_ACTIVE(1277540472)) {
			STREAMING::_REQUEST_IMAP(1277540472);
		}

		if (!STREAMING::_IS_IMAP_ACTIVE(1169511062)) {
			STREAMING::_REQUEST_IMAP(1169511062);
		}

		if (!STREAMING::_IS_IMAP_ACTIVE(897624424)) {
			STREAMING::_REQUEST_IMAP(897624424);
		}

		if (!STREAMING::_IS_IMAP_ACTIVE(-1266106154)) {
			STREAMING::_REQUEST_IMAP(-1266106154);
		}

		if (!STREAMING::_IS_IMAP_ACTIVE(-574996782)) {
			STREAMING::_REQUEST_IMAP(-574996782);
		}

		if (!STREAMING::_IS_IMAP_ACTIVE(-1377975054)) {
			STREAMING::_REQUEST_IMAP(-1377975054);
		}

		if (!STREAMING::_IS_IMAP_ACTIVE(1614255891)) {
			STREAMING::_REQUEST_IMAP(1614255891);
		}

		if (!STREAMING::_IS_IMAP_ACTIVE(258104717)) {
			STREAMING::_REQUEST_IMAP(258104717);
		}

		if (!STREAMING::_IS_IMAP_ACTIVE(1044079550)) {
			STREAMING::_REQUEST_IMAP(1044079550);
		}

		if (!STREAMING::_IS_IMAP_ACTIVE(-37875204)) {
			STREAMING::_REQUEST_IMAP(-37875204);
		}

		if (!STREAMING::_IS_IMAP_ACTIVE(1861460906)) {
			STREAMING::_REQUEST_IMAP(1861460906);
		}





		if (IsKeyJustUp(VK_KEY_0)) {
			CAM::RENDER_SCRIPT_CAMS(0, 0, 500, 1, 0, 0);
		}
		if (IsKeyJustUp(VK_KEY_1)) {
			CAM::RENDER_SCRIPT_CAMS(1, 0, 500, 1, 0, 0);
		}


		if (arthur_mode || epilogue) {
			weaponLocker(playerPos);
			bedBlip(playerPos);
		}

		if (arthur_mode || epilogue) {
			for (int i = 0; i < 3; i++) {
				if (distanceBetween(playerPos, outfittersCoords[i]) < 30.f) { //TODO add interior check
					if (!MAP::DOES_BLIP_EXIST(ridgeOutfittersBlips[i]))
					{

						if ((i == 2 && Houses[7]) || (i != 2 && Houses[i + 1])) {
							ridgeOutfittersBlips[i] = MAP::_BLIP_ADD_FOR_COORD(0x63351D54, outfittersCoords[i].x, outfittersCoords[i].y, outfittersCoords[i].z);
							MAP::_BLIP_SET_MODIFIER(ridgeOutfittersBlips[i], MISC::GET_HASH_KEY("BLIP_MODIFIER_RADAR_EDGE_NEVER"));
							MAP::SET_BLIP_SPRITE(ridgeOutfittersBlips[i], MISC::GET_HASH_KEY("blip_ambient_quartermaster"), false);
							MAP::_SET_BLIP_NAME_FROM_PLAYER_STRING(ridgeOutfittersBlips[i], (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "House Customization"));

						}
					}
				}
				else {
					Misc::removeBlipSafe(ridgeOutfittersBlips[i]);
				}
			}
		}



		HUD::_UIPROMPT_SET_ENABLED(Prompt_Menu, 0);
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Menu, 0);

		if (arthur_mode || epilogue) {
			if (distanceBetween(playerPos, ridgeOutfitters) < 2.f && Houses[1]) {
				HUD::_UIPROMPT_SET_GROUP(Prompt_Menu, -2019190071, 0);

				HUD::_UIPROMPT_SET_ACTIVE_GROUP_THIS_FRAME(-2019190071, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Ridge View"), 1, 0, 0, 0);


				if (!menu_on) {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Menu, 1);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Menu, 1);
				}
				Menu();
			}

			if (distanceBetween(playerPos, strawOutfitters) < 2.f && Houses[2]) {
				HUD::_UIPROMPT_SET_GROUP(Prompt_Menu, -2019190071, 0);

				HUD::_UIPROMPT_SET_ACTIVE_GROUP_THIS_FRAME(-2019190071, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Shepherds Rise"), 1, 0, 0, 0);



				if (!menu_on) {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Menu, 1);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Menu, 1);
				}
				Menu2();
			}
			if (distanceBetween(playerPos, argilsOutfitters) < 2.f && Houses[7]) {
				HUD::_UIPROMPT_SET_GROUP(Prompt_Menu, -2019190071, 0);

				HUD::_UIPROMPT_SET_ACTIVE_GROUP_THIS_FRAME(-2019190071, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Argil Rise"), 1, 0, 0, 0);




				if (!menu_on) {
					HUD::_UIPROMPT_SET_ENABLED(Prompt_Menu, 1);
					HUD::_UIPROMPT_SET_VISIBLE(Prompt_Menu, 1);
				}
				Menu3();
			}



			if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Menu)) {
				menu_on = 1;
				//ENTITY::SET_ENTITY_VISIBLE(player, 0);


				if (distanceBetween(playerPos, ridgeOutfitters) < 2.f && Houses[1]) {
					TASK::TASK_START_SCENARIO_AT_POSITION(player, MISC::GET_HASH_KEY("WORLD_PLAYER_PRPTY_FAST_TRAVEL"), 1778.486, 459.400, 111.6, 290, -1, true, false, 0, 0, false);


					if (CAM::DOES_CAM_EXIST(houseCam)) {
						CAM::DESTROY_CAM(houseCam, 1);
					}
					if (CAM::DOES_CAM_EXIST(outsideCam)) {
						CAM::DESTROY_CAM(outsideCam, 1);
					}


					houseCam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1774.191, 457.802, 113.f, 0, 0, 0, 60, 1, 2);
					outsideCam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1774.191, 454.802, 112.283, 0, 0, 0, 60, 1, 2);

				}

				if (distanceBetween(playerPos, strawOutfitters) < 2.f && Houses[2]) {
					TASK::TASK_START_SCENARIO_AT_POSITION(player, MISC::GET_HASH_KEY("WORLD_PLAYER_PRPTY_FAST_TRAVEL"), -1559.049, 254.442, 112.99, 288, -1, true, false, 0, 0, false);

					if (CAM::DOES_CAM_EXIST(houseCam)) {
						CAM::DESTROY_CAM(houseCam, 1);
					}
					if (CAM::DOES_CAM_EXIST(outsideCam)) {
						CAM::DESTROY_CAM(outsideCam, 1);
					}

					houseCam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", -1561.542, 243.617, 115.574f, 0, 0, 0, 60, 1, 2);
					outsideCam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", -1561.542, 243.617, 113.574f, 0, 0, 0, 60, 1, 2);
				}
				if (distanceBetween(playerPos, argilsOutfitters) < 2.f && Houses[7]) {
					TASK::TASK_START_SCENARIO_AT_POSITION(player, MISC::GET_HASH_KEY("WORLD_PLAYER_PRPTY_FAST_TRAVEL"), 1462.145, -1578.848, 70.84, 66, -1, true, false, 0, 0, false);

					if (CAM::DOES_CAM_EXIST(houseCam)) {
						CAM::DESTROY_CAM(houseCam, 1);
					}
					if (CAM::DOES_CAM_EXIST(outsideCam)) {
						CAM::DESTROY_CAM(outsideCam, 1);
					}

					houseCam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1468.489f, -1579.170f, 72.080f, 0, 0, 0, 60, 1, 2);
					outsideCam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 1460.451f, -1589.812f, 71.837f, 0, 0, 0, 60, 1, 2);

					

				}


				
			}
		}




		Entity ent;
		if (PLAYER::IS_PLAYER_TARGETTING_ANYTHING(0)) {
			if (PLAYER::GET_PLAYER_TARGET_ENTITY(0, &ent)) {
				if (ENTITY::IS_ENTITY_A_PED(ent)) {
					Ped targetPed = ent;





					if (!Houses[0]) {
						// U_M_M_ValHotelOwner_01
						if (PED::IS_PED_MODEL(targetPed, MISC::GET_HASH_KEY("U_M_M_NbxBartender_01"))) {
							/*
							//	HUD::_UIPROMPT_SET_AMBIENT_GROUP_THIS_FRAME(ent, 1.f, 1, 1, -484761727, "WARDROBE", 2);
							textLabel = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Buy Room ($3000)"); //create text Rent Premium Room ($5.00)

							HUD::_UIPROMPT_SET_TEXT(PromptRoom, (char*)textLabel); //set text

							HUD::_UIPROMPT_SET_VISIBLE(PromptRoom, 1);
							if (!Houses[0] && MONEY::_MONEY_GET_CASH_BALANCE() >= housesPrice[0] * 100) {
								HUD::_UIPROMPT_SET_ENABLED(PromptRoom, 1);

							}
							else {
								HUD::_UIPROMPT_SET_ENABLED(PromptRoom, 0);
							}





							if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(PromptRoom)) {
								int money = MONEY::_MONEY_GET_CASH_BALANCE();
								MONEY::_MONEY_DECREMENT_CASH_BALANCE(housesPrice[0] * 100);
								//MONEY::_MONEY_INCREMENT_CASH_BALANCE(money - housesPrice[0] * 100, 1);

								MAP::REMOVE_BLIP(&housesBlip[0]);


								Toasts::showAdvancedNotification("Property Purchased", "You are now the owner of the ~COLOR_GOLD~Saint Denis Hotel Room", "toast_log_blips", "blip_robbery_home", 200);


								Houses[0] = 1;
							}





							HUD::_UIPROMPT_SET_GROUP(PromptRoom, HUD::_UIPROMPT_GET_GROUP_ID_FOR_TARGET_ENTITY(ent), 0);


							*/
						}

					}

					if (!Houses[3]) {
						// U_M_M_ValHotelOwner_01
						if (PED::IS_PED_MODEL(targetPed, MISC::GET_HASH_KEY("U_M_M_ValBartender_01"))) {
							/*
							//	HUD::_UIPROMPT_SET_AMBIENT_GROUP_THIS_FRAME(ent, 1.f, 1, 1, -484761727, "WARDROBE", 2);
							textLabel = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Buy Room ($1500)"); //create text Rent Premium Room ($5.00)

							HUD::_UIPROMPT_SET_TEXT(PromptRoom, (char*)textLabel); //set text



							HUD::_UIPROMPT_SET_VISIBLE(PromptRoom, 1);
							if (!Houses[3] && MONEY::_MONEY_GET_CASH_BALANCE() >= housesPrice[3] * 100) {
								HUD::_UIPROMPT_SET_ENABLED(PromptRoom, 1);

							}
							else {
								HUD::_UIPROMPT_SET_ENABLED(PromptRoom, 0);

							}


							if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(PromptRoom)) {
								int money = MONEY::_MONEY_GET_CASH_BALANCE();
								MONEY::_MONEY_DECREMENT_CASH_BALANCE(housesPrice[3] * 100);
								//MONEY::_MONEY_INCREMENT_CASH_BALANCE(money - housesPrice[3] * 100, 1);

								MAP::REMOVE_BLIP(&housesBlip[3]);

								Toasts::showAdvancedNotification("Property Purchased", "You are now the owner of the ~COLOR_GOLD~Valentine Saloon Room", "toast_log_blips", "blip_robbery_home", 200);


								Houses[3] = 1;
							}



							HUD::_UIPROMPT_SET_GROUP(PromptRoom, HUD::_UIPROMPT_GET_GROUP_ID_FOR_TARGET_ENTITY(ent), 0);
							*/


						}

					}

					if (!Houses[4]) {
						// U_M_M_ValHotelOwner_01
						if (PED::IS_PED_MODEL(targetPed, MISC::GET_HASH_KEY("U_M_M_STRWELCOMECENTER_01"))) {

							//	HUD::_UIPROMPT_SET_AMBIENT_GROUP_THIS_FRAME(ent, 1.f, 1, 1, -484761727, "WARDROBE", 2);
							textLabel = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Buy Room ($2000)"); //create text Rent Premium Room ($5.00)

							HUD::_UIPROMPT_SET_TEXT(PromptRoom, (char*)textLabel); //set text



							HUD::_UIPROMPT_SET_VISIBLE(PromptRoom, 1);
							if (!Houses[4] && MONEY::_MONEY_GET_CASH_BALANCE() >= housesPrice[4] * 100) {
								HUD::_UIPROMPT_SET_ENABLED(PromptRoom, 1);

							}
							else {
								HUD::_UIPROMPT_SET_ENABLED(PromptRoom, 0);

							}


							if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(PromptRoom)) {
								int money = MONEY::_MONEY_GET_CASH_BALANCE();
								MONEY::_MONEY_DECREMENT_CASH_BALANCE(housesPrice[4] * 100);
								//MONEY::_MONEY_INCREMENT_CASH_BALANCE(money - housesPrice[4] * 100, 1);

								MAP::REMOVE_BLIP(&housesBlip[4]);

								Toasts::showAdvancedNotification("Property Purchased", "You are now the owner of the ~COLOR_GOLD~Strawberry Hotel Room", "toast_log_blips", "blip_robbery_home", 200);


								Houses[4] = 1;
							}



							HUD::_UIPROMPT_SET_GROUP(PromptRoom, HUD::_UIPROMPT_GET_GROUP_ID_FOR_TARGET_ENTITY(ent), 0);



						}

					}

					if (!Houses[5]) {
						// U_M_M_ValHotelOwner_01
						if (PED::IS_PED_MODEL(targetPed, MISC::GET_HASH_KEY("U_M_M_RhdBartender_01"))) {

							//	HUD::_UIPROMPT_SET_AMBIENT_GROUP_THIS_FRAME(ent, 1.f, 1, 1, -484761727, "WARDROBE", 2);
							textLabel = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Buy Room ($2500)"); //create text Rent Premium Room ($5.00)

							HUD::_UIPROMPT_SET_TEXT(PromptRoom, (char*)textLabel); //set text



							HUD::_UIPROMPT_SET_VISIBLE(PromptRoom, 1);
							if (!Houses[5] && MONEY::_MONEY_GET_CASH_BALANCE() >= housesPrice[5] * 100) {
								HUD::_UIPROMPT_SET_ENABLED(PromptRoom, 1);

							}
							else {
								HUD::_UIPROMPT_SET_ENABLED(PromptRoom, 0);

							}


							if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(PromptRoom)) {
								int money = MONEY::_MONEY_GET_CASH_BALANCE();
								MONEY::_MONEY_DECREMENT_CASH_BALANCE(housesPrice[5] * 100);
								//MONEY::_MONEY_INCREMENT_CASH_BALANCE(money - housesPrice[5] * 100, 0);

								MAP::REMOVE_BLIP(&housesBlip[5]);

								Toasts::showAdvancedNotification("Property Purchased", "You are now the owner of the ~COLOR_GOLD~Rhodes Saloon Room", "toast_log_blips", "blip_robbery_home", 200);


								Houses[5] = 1;
							}



							HUD::_UIPROMPT_SET_GROUP(PromptRoom, HUD::_UIPROMPT_GET_GROUP_ID_FOR_TARGET_ENTITY(ent), 0);



						}

					}

					if (!Houses[6]) {
						// U_M_M_ValHotelOwner_01
						if (PED::IS_PED_MODEL(targetPed, MISC::GET_HASH_KEY("U_M_M_ValHotelOwner_01"))) {

							//	HUD::_UIPROMPT_SET_AMBIENT_GROUP_THIS_FRAME(ent, 1.f, 1, 1, -484761727, "WARDROBE", 2);
							textLabel = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Buy Room ($2300)"); //create text Rent Premium Room ($5.00)

							HUD::_UIPROMPT_SET_TEXT(PromptRoom, (char*)textLabel); //set text



							HUD::_UIPROMPT_SET_VISIBLE(PromptRoom, 1);
							if (!Houses[6] && MONEY::_MONEY_GET_CASH_BALANCE() >= housesPrice[6] * 100) {
								HUD::_UIPROMPT_SET_ENABLED(PromptRoom, 1);

							}
							else {
								HUD::_UIPROMPT_SET_ENABLED(PromptRoom, 0);

							}


							if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(PromptRoom)) {
								int money = MONEY::_MONEY_GET_CASH_BALANCE();
								MONEY::_MONEY_DECREMENT_CASH_BALANCE(housesPrice[6] * 100);
								//MONEY::_MONEY_INCREMENT_CASH_BALANCE(money - housesPrice[5] * 100, 0);

								MAP::REMOVE_BLIP(&housesBlip[6]);

								Toasts::showAdvancedNotification("Property Purchased", "You are now the owner of the ~COLOR_GOLD~Valentine Hotel Room", "toast_log_blips", "blip_robbery_home", 200);


								Houses[6] = 1;
							}



							HUD::_UIPROMPT_SET_GROUP(PromptRoom, HUD::_UIPROMPT_GET_GROUP_ID_FOR_TARGET_ENTITY(ent), 0);



						}

					}




				}
			}
		}






		//HUD::_UIPROMPT_SET_VISIBLE(PromptRoom, 1);
		//HUD::_UIPROMPT_SET_GROUP(PromptRoom, -484761727, 0);

		//-484761727






		OBJECT::_ADD_DOOR_TO_SYSTEM_NEW(2188892390, 1, 1, 1, 1, 1, 1);
		OBJECT::_ADD_DOOR_TO_SYSTEM_NEW(2472180395, 1, 1, 1, 1, 1, 1);

		OBJECT::_ADD_DOOR_TO_SYSTEM_NEW(3221874820, 1, 1, 1, 1, 1, 1);
		OBJECT::_ADD_DOOR_TO_SYSTEM_NEW(2366407202, 1, 1, 1, 1, 1, 1);

		OBJECT::_ADD_DOOR_TO_SYSTEM_NEW(1087218607, 1, 1, 1, 1, 1, 1);

		OBJECT::_ADD_DOOR_TO_SYSTEM_NEW(1562553736, 1, 1, 1, 1, 1, 1);

		OBJECT::_ADD_DOOR_TO_SYSTEM_NEW(2046695029, 1, 1, 1, 1, 1, 1);


		OBJECT::_ADD_DOOR_TO_SYSTEM_NEW(3693364451, 1, 1, 1, 1, 1, 1);


		OBJECT::_ADD_DOOR_TO_SYSTEM_NEW(3327934361, 1, 1, 1, 1, 1, 1);
		OBJECT::_ADD_DOOR_TO_SYSTEM_NEW(3014302262, 1, 1, 1, 1, 1, 1);




		HUD::_UIPROMPT_SET_VISIBLE(PromptBuy, 0);
		HUD::_UIPROMPT_SET_ENABLED(PromptBuy, 0);




		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Sleep2, 0);
		HUD::_UIPROMPT_SET_ENABLED(Prompt_Sleep2, 0);
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Leave, 0);
		HUD::_UIPROMPT_SET_ENABLED(Prompt_Leave, 0);

		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Back2, 0);
		HUD::_UIPROMPT_SET_ENABLED(Prompt_Back2, 0);


		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Nap1, 0);
		HUD::_UIPROMPT_SET_ENABLED(Prompt_Nap1, 0);
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Nap2, 0);
		HUD::_UIPROMPT_SET_ENABLED(Prompt_Nap2, 0);
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Nap3, 0);
		HUD::_UIPROMPT_SET_ENABLED(Prompt_Nap3, 0);


		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Sleep, 0);
		HUD::_UIPROMPT_SET_ENABLED(Prompt_Sleep, 0);
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Sit, 0);
		HUD::_UIPROMPT_SET_ENABLED(Prompt_Sit, 0);

		if (distanceBetween(playerPos, roomWardrobes[0]) < 1.f ||
			distanceBetween(playerPos, roomWardrobes[1]) < 1.f ||
			distanceBetween(playerPos, roomWardrobes[2]) < 1.f ||
			distanceBetween(playerPos, roomWardrobes[3]) < 1.f ||
			distanceBetween(playerPos, roomWardrobes[4]) < 1.f ||
			distanceBetween(playerPos, roomWardrobes[5]) < 1.f) {

			HUD::_UIPROMPT_SET_GROUP(Prompt_Locker, -2019190071, 0);

			HUD::_UIPROMPT_SET_ACTIVE_GROUP_THIS_FRAME(-2019190071, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Wardrobe"), 1, 0, 0, 0);

			HUD::_UIPROMPT_SET_ENABLED(Prompt_Locker, 1);
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Locker, 1);

		}

		if (distanceBetween(playerPos, roomBeds[0]) < 1.f ||
			distanceBetween(playerPos, roomBeds[1]) < 1.f ||
			distanceBetween(playerPos, roomBeds[2]) < 1.f ||
			distanceBetween(playerPos, roomBeds[3]) < 1.f ||
			distanceBetween(playerPos, roomBeds[4]) < 1.f ||
			distanceBetween(playerPos, roomBeds[5]) < 1.f) {


			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Sleep, 1);
			HUD::_UIPROMPT_SET_ENABLED(Prompt_Sleep, 1);
			HUD::_UIPROMPT_SET_VISIBLE(Prompt_Sit, 1);
			HUD::_UIPROMPT_SET_ENABLED(Prompt_Sit, 1);




			if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Sit)) {
				TASK::CLEAR_PED_TASKS(player, 1, 1);

				if (distanceBetween(playerPos, roomBeds[0]) < 1.f) {
					TASK::TASK_START_SCENARIO_AT_POSITION(player, MISC::GET_HASH_KEY("PROP_PLAYER_SLEEP_BED"), -327.35, 766.186, 121.2, 276.815, -1, true, false, 0, 0, false);
				}
				if (distanceBetween(playerPos, roomBeds[1]) < 1.f) {
					TASK::TASK_START_SCENARIO_AT_POSITION(player, MISC::GET_HASH_KEY("PROP_PLAYER_SLEEP_BED"), roomBeds[1].x - 0.5, roomBeds[1].y, roomBeds[1].z - 0.5, 276.815, -1, true, false, 0, 0, false);
				}
				if (distanceBetween(playerPos, roomBeds[2]) < 1.f) {
					TASK::TASK_START_SCENARIO_AT_POSITION(player, MISC::GET_HASH_KEY("PROP_PLAYER_SLEEP_BED"), roomBeds[2].x, roomBeds[2].y, roomBeds[2].z, 276.815, -1, true, false, 0, 0, false);
				}
				if (distanceBetween(playerPos, roomBeds[3]) < 1.f) {
					TASK::TASK_START_SCENARIO_AT_POSITION(player, MISC::GET_HASH_KEY("PROP_PLAYER_SLEEP_BED"), roomBeds[3].x - 0.5, roomBeds[3].y, roomBeds[3].z - 0.5, 276.815, -1, true, false, 0, 0, false);
				}
				if (distanceBetween(playerPos, roomBeds[4]) < 1.f) {
					TASK::TASK_START_SCENARIO_AT_POSITION(player, MISC::GET_HASH_KEY("PROP_PLAYER_SLEEP_BED"), roomBeds[4].x + 0.22, roomBeds[4].y, roomBeds[4].z - 0.5, 87.874, -1, true, false, 0, 0, false);
				}
				if (distanceBetween(playerPos, roomBeds[5]) < 1.f) {
					TASK::TASK_START_SCENARIO_AT_POSITION(player, MISC::GET_HASH_KEY("PROP_PLAYER_SLEEP_BED"), roomBeds[5].x , roomBeds[5].y - 0.5, roomBeds[5].z - 0.5, 350.875, -1, true, false, 0, 0, false);
				}
				is_sitting_bed = 1;
			}

			if (is_sitting_bed) {
				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Sleep, 0);
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Sleep, 0);
				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Sit, 0);
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Sit, 0);

				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Sleep2, 1);
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Sleep2, 1);
				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Leave, 1);
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Leave, 1);


			}

			if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Sleep2) || HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(Prompt_Sleep)) {
				choose_sleep = 1;
			}

			if (choose_sleep) {
				HUD::_UIPROMPT_SET_ACTIVE_GROUP_THIS_FRAME(-2019190071, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Sleep"), 1, 0, 0, 0);

				stringstream nap1Stream;
				stringstream nap2Stream;
				stringstream nap3Stream;

				if (CLOCK::GET_CLOCK_HOURS() >= 6 && CLOCK::GET_CLOCK_HOURS() < 12) {

					nap1Stream << "Noon (";
					nap1Stream << 12 - CLOCK::GET_CLOCK_HOURS();
					nap1Stream << "hrs)";
					HUD::_UIPROMPT_SET_TEXT(Prompt_Nap1, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", nap1Stream.str().c_str()));
					nap2Stream << "Evening (";
					nap2Stream << 18 - CLOCK::GET_CLOCK_HOURS();
					nap2Stream << "hrs)";
					HUD::_UIPROMPT_SET_TEXT(Prompt_Nap2, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", nap2Stream.str().c_str()));
					nap3Stream << "Night (";
					nap3Stream << 24 - CLOCK::GET_CLOCK_HOURS();
					nap3Stream << "hrs)";
					HUD::_UIPROMPT_SET_TEXT(Prompt_Nap3, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", nap3Stream.str().c_str()));


					if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Nap1)) {
						sleepSeq(12 - CLOCK::GET_CLOCK_HOURS());
					}
					if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Nap2)) {
						sleepSeq(18 - CLOCK::GET_CLOCK_HOURS());
					}
					if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Nap3)) {
						sleepSeq(24 - CLOCK::GET_CLOCK_HOURS());
					}



				}
				if (CLOCK::GET_CLOCK_HOURS() >= 12 && CLOCK::GET_CLOCK_HOURS() < 18) {

					nap1Stream << "Evening (";
					nap1Stream << 18 - CLOCK::GET_CLOCK_HOURS();
					nap1Stream << "hrs)";
					HUD::_UIPROMPT_SET_TEXT(Prompt_Nap1, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", nap1Stream.str().c_str()));
					nap2Stream << "Night (";
					nap2Stream << 24 - CLOCK::GET_CLOCK_HOURS();
					nap2Stream << "hrs)";
					HUD::_UIPROMPT_SET_TEXT(Prompt_Nap2, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", nap2Stream.str().c_str()));
					nap3Stream << "Morning (";
					nap3Stream << 30 - CLOCK::GET_CLOCK_HOURS();
					nap3Stream << "hrs)";
					HUD::_UIPROMPT_SET_TEXT(Prompt_Nap3, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", nap3Stream.str().c_str()));

					if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Nap1)) {
						sleepSeq(18 - CLOCK::GET_CLOCK_HOURS());
					}
					if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Nap2)) {
						sleepSeq(24 - CLOCK::GET_CLOCK_HOURS());
					}
					if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Nap3)) {
						sleepSeq(30 - CLOCK::GET_CLOCK_HOURS());
					}


				}
				if (CLOCK::GET_CLOCK_HOURS() >= 18 && CLOCK::GET_CLOCK_HOURS() <= 23) {
					nap1Stream << "Night (";
					nap1Stream << 24 - CLOCK::GET_CLOCK_HOURS();
					nap1Stream << "hrs)";
					HUD::_UIPROMPT_SET_TEXT(Prompt_Nap1, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", nap1Stream.str().c_str()));
					nap2Stream << "Morning (";
					nap2Stream << 30 - CLOCK::GET_CLOCK_HOURS();
					nap2Stream << "hrs)";
					HUD::_UIPROMPT_SET_TEXT(Prompt_Nap2, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", nap2Stream.str().c_str()));
					nap3Stream << "Noon (";
					nap3Stream << 36 - CLOCK::GET_CLOCK_HOURS();
					nap3Stream << "hrs)";
					HUD::_UIPROMPT_SET_TEXT(Prompt_Nap3, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", nap3Stream.str().c_str()));

					if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Nap1)) {
						sleepSeq(24 - CLOCK::GET_CLOCK_HOURS());
					}
					if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Nap2)) {
						sleepSeq(30 - CLOCK::GET_CLOCK_HOURS());
					}
					if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Nap3)) {
						sleepSeq(36 - CLOCK::GET_CLOCK_HOURS());
					}


				}
				if (CLOCK::GET_CLOCK_HOURS() > 23 || (CLOCK::GET_CLOCK_HOURS() >= 0 && CLOCK::GET_CLOCK_HOURS() < 6)) {
					nap1Stream << "Morning (";
					nap1Stream << 6 - CLOCK::GET_CLOCK_HOURS();
					nap1Stream << "hrs)";
					HUD::_UIPROMPT_SET_TEXT(Prompt_Nap1, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", nap1Stream.str().c_str()));
					nap2Stream << "Noon (";
					nap2Stream << 12 - CLOCK::GET_CLOCK_HOURS();
					nap2Stream << "hrs)";
					HUD::_UIPROMPT_SET_TEXT(Prompt_Nap2, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", nap2Stream.str().c_str()));
					nap3Stream << "Evening (";
					nap3Stream << 18 - CLOCK::GET_CLOCK_HOURS();
					nap3Stream << "hrs)";
					HUD::_UIPROMPT_SET_TEXT(Prompt_Nap3, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", nap3Stream.str().c_str()));


					if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Nap1)) {
						sleepSeq(6 - CLOCK::GET_CLOCK_HOURS());
					}
					if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Nap2)) {
						sleepSeq(12 - CLOCK::GET_CLOCK_HOURS());
					}
					if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Nap3)) {
						sleepSeq(18 - CLOCK::GET_CLOCK_HOURS());
					}
				}




				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Sleep, 0);
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Sleep, 0);
				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Sit, 0);
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Sit, 0);

				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Sleep2, 0);
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Sleep2, 0);
				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Leave, 0);
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Leave, 0);



				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Back2, 1);
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Back2, 1);


				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Nap1, 1);
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Nap1, 1);
				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Nap2, 1);
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Nap2, 1);
				HUD::_UIPROMPT_SET_VISIBLE(Prompt_Nap3, 1);
				HUD::_UIPROMPT_SET_ENABLED(Prompt_Nap3, 1);


			}
			else {
				HUD::_UIPROMPT_SET_ACTIVE_GROUP_THIS_FRAME(-2019190071, (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Bed"), 1, 0, 0, 0);

			}

			if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Back2)) {
				choose_sleep = 0;
			}

			if (HUD::_UIPROMPT_IS_JUST_RELEASED(Prompt_Leave)) {
				TASK::CLEAR_PED_TASKS(player, 1, 1);
				is_sitting_bed = 0;
			}
		}

		//PROP_PLAYER_SLEEP_BED



		for (int i = 0; i <= houseLimit - 1; i++) {

			PED::ADD_SCENARIO_BLOCKING_AREA(housesVecs[i].x - 7.5, housesVecs[i].y - 7.5, housesVecs[i].z - 7.5, housesVecs[i].x + 7.5, housesVecs[i].y + 7.5, housesVecs[i].z + 7.5, false, 15);


			if (distanceBetween(playerPos, housesBuy[i]) < 3.f) {

				if (!Houses[i]) {
					HUD::_UIPROMPT_SET_VISIBLE(PromptBuy, 1);
					if (MONEY::_MONEY_GET_CASH_BALANCE() >= housesPrice[i] * 100) {

						HUD::_UIPROMPT_SET_ENABLED(PromptBuy, 1);
					}
					else {
						HUD::_UIPROMPT_SET_ENABLED(PromptBuy, 0);
					}
				}
				else {
					HUD::_UIPROMPT_SET_ENABLED(PromptBuy, 0);
					HUD::_UIPROMPT_SET_VISIBLE(PromptBuy, 0);
				}

			}
		}


		if (arthur_mode || epilogue) {
			for (int i = 0; i <= houseLimit - 1; i++) {
				if (Houses[i]) {
					if (distanceBetween(playerPos, housesVecs[i]) > 6.f) {
						if (!MAP::DOES_BLIP_EXIST(housesBlip[i]))
						{

							housesBlip[i] = MAP::_BLIP_ADD_FOR_COORD(0x63351D54, housesVecs[i].x, housesVecs[i].y, housesVecs[i].z);
							MAP::_BLIP_SET_MODIFIER(housesBlip[i], MISC::GET_HASH_KEY("BLIP_MODIFIER_RADAR_EDGE_NEVER"));
							MAP::SET_BLIP_SPRITE(housesBlip[i], MISC::GET_HASH_KEY("blip_proc_home"), false);
							MAP::_SET_BLIP_NAME_FROM_PLAYER_STRING(housesBlip[i], (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "House"));

						}
					}
					else {
						if (MAP::DOES_BLIP_EXIST(housesBlip[i])) {
							MAP::REMOVE_BLIP(&housesBlip[i]);
						}
					}



				}
				else {
					if (!MAP::DOES_BLIP_EXIST(housesBlip[i]))
					{
						if (i != 3 && i != 0) {
							housesBlip[i] = MAP::_BLIP_ADD_FOR_COORD(0xEC972124, housesBuy[i].x, housesBuy[i].y, housesBuy[i].z);
							MAP::_BLIP_SET_MODIFIER(housesBlip[i], MISC::GET_HASH_KEY("BLIP_MODIFIER_RADAR_EDGE_NEVER"));
							MAP::SET_BLIP_SPRITE(housesBlip[i], MISC::GET_HASH_KEY("blip_robbery_home"), false);
							MAP::_SET_BLIP_NAME_FROM_PLAYER_STRING(housesBlip[i], (char*)MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "House to buy"));
						}
					}
				}
			}
		}


		if (distanceBetween(playerPos, housesBuy[0]) < 3.f) {
			HUD::_UIPROMPT_SET_ENABLED(PromptBuy, 0);
			HUD::_UIPROMPT_SET_VISIBLE(PromptBuy, 0);
		}
		if (arthur_mode || epilogue) {
			if (distanceBetween(playerPos, housesBuy[1]) < 3.f) {
				textLabel = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Buy Property ($18000)"); //create text Rent Premium Room ($5.00)
				if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(PromptBuy)) {



					int money = MONEY::_MONEY_GET_CASH_BALANCE();

					//MONEY::_MONEY_INCREMENT_CASH_BALANCE(money - housesPrice[1] * 100, 1);

					if (!Houses[1]) {
						BuyRoom("Houses/ridge_base.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(housesPrice[1] * 100);
						Toasts::showAdvancedNotification("Property Purchased", "You are now the owner of ~COLOR_GOLD~Ridge View cabin", "toast_log_blips", "blip_robbery_home", 200);
					}



					MAP::REMOVE_BLIP(&housesBlip[1]);


					Houses[1] = 1;
				}
			}

			if (distanceBetween(playerPos, housesBuy[2]) < 3.f) {
				textLabel = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Buy Property ($12000)");
				if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(PromptBuy)) {



					int money = MONEY::_MONEY_GET_CASH_BALANCE();
					//MONEY::_MONEY_DECREMENT_CASH_BALANCE(housesPrice[2] * 100);
					//MONEY::_MONEY_INCREMENT_CASH_BALANCE(money - housesPrice[2] * 100, 1);

					if (!Houses[2]) {
						BuyRoom("Houses/shepherds_base.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(housesPrice[2] * 100);
						Toasts::showAdvancedNotification("Property Purchased", "You are now the owner of ~COLOR_GOLD~Shepherds Rise cabin", "toast_log_blips", "blip_robbery_home", 200);
					}


					MAP::REMOVE_BLIP(&housesBlip[2]);


					Houses[2] = 1;
				}
			}


			if (distanceBetween(playerPos, housesBuy[7]) < 3.f) {
				textLabel = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Buy Property ($10300)"); //create text Rent Premium Room ($5.00)
				if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(PromptBuy)) {
					int money = MONEY::_MONEY_GET_CASH_BALANCE();
					if (!Houses[7]) {
						BuyRoom("Houses/argil_base.xml", mainObjects);
						MONEY::_MONEY_DECREMENT_CASH_BALANCE(housesPrice[7] * 100);
						Toasts::showAdvancedNotification("Property Purchased", "You are now the owner of ~COLOR_GOLD~Argil Rise cabin", "toast_log_blips", "blip_robbery_home", 200);
					}

					MAP::REMOVE_BLIP(&housesBlip[7]);


					Houses[7] = 1;
				}
			}

		}


		if (distanceBetween(playerPos, housesBuy[3]) < 3.f) {
			HUD::_UIPROMPT_SET_ENABLED(PromptBuy, 0);
			HUD::_UIPROMPT_SET_VISIBLE(PromptBuy, 0);

			textLabel = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Buy Property ($1500)");
			if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(PromptBuy)) {



				int money = MONEY::_MONEY_GET_CASH_BALANCE();
				MONEY::_MONEY_DECREMENT_CASH_BALANCE(housesPrice[3] * 100);
				//MONEY::_MONEY_INCREMENT_CASH_BALANCE(money - housesPrice[3] * 100, 1);


				MAP::REMOVE_BLIP(&housesBlip[3]);


				Houses[3] = 1;
			}
		}
		if (distanceBetween(playerPos, housesBuy[4]) < 3.f) {
			HUD::_UIPROMPT_SET_ENABLED(PromptBuy, 0);
			HUD::_UIPROMPT_SET_VISIBLE(PromptBuy, 0);

			textLabel = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Buy Property ($2000)"); //create text Rent Premium Room ($5.00)
			if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(PromptBuy)) {



				int money = MONEY::_MONEY_GET_CASH_BALANCE();
				MONEY::_MONEY_DECREMENT_CASH_BALANCE(housesPrice[4] * 100);
				//MONEY::_MONEY_INCREMENT_CASH_BALANCE(money - housesPrice[4] * 100, 1);


				MAP::REMOVE_BLIP(&housesBlip[4]);


				Houses[4] = 1;
			}
		}
		if (distanceBetween(playerPos, housesBuy[5]) < 3.f) {
			HUD::_UIPROMPT_SET_ENABLED(PromptBuy, 0);
			HUD::_UIPROMPT_SET_VISIBLE(PromptBuy, 0);

			textLabel = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Buy Property ($2500)"); //create text Rent Premium Room ($5.00)
			if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(PromptBuy)) {



				int money = MONEY::_MONEY_GET_CASH_BALANCE();
				MONEY::_MONEY_DECREMENT_CASH_BALANCE(housesPrice[5] * 100);
				//MONEY::_MONEY_INCREMENT_CASH_BALANCE(money - housesPrice[5] * 100, 0);


				MAP::REMOVE_BLIP(&housesBlip[5]);


				Houses[5] = 1;
			}
		}
		if (distanceBetween(playerPos, housesBuy[6]) < 3.f) {
			HUD::_UIPROMPT_SET_ENABLED(PromptBuy, 0);
			HUD::_UIPROMPT_SET_VISIBLE(PromptBuy, 0);

			textLabel = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Buy Property ($2300)"); //create text Rent Premium Room ($5.00)
			if (HUD::_UIPROMPT_HAS_HOLD_MODE_COMPLETED(PromptBuy)) {



				int money = MONEY::_MONEY_GET_CASH_BALANCE();
				MONEY::_MONEY_DECREMENT_CASH_BALANCE(housesPrice[6] * 100);
				//MONEY::_MONEY_INCREMENT_CASH_BALANCE(money - housesPrice[5] * 100, 0);

				if (!Houses[6]) {
					Toasts::showAdvancedNotification("Property Purchased", "You are now the owner of ~COLOR_GOLD~Argil Rise cabin", "toast_log_blips", "blip_robbery_home", 200);
				}

				MAP::REMOVE_BLIP(&housesBlip[6]);


				Houses[6] = 1;
			}
		}




		next_cash = MONEY::_MONEY_GET_CASH_BALANCE();
		if (MISC::GET_GAME_TIMER() > cash_timer) {
			cash_timer = MISC::GET_GAME_TIMER() + 10000;

			current_cash = MONEY::_MONEY_GET_CASH_BALANCE();
		}

		int test;


		if (distanceBetween(Misc::toVector3(1328.224, -1293.651, 77.016), playerPos) < 15.f) {
			test = MONEY::_MONEY_GET_CASH_BALANCE() + 5000 * 100;
			if (test <= current_cash) {
				if (!Houses[7]) {
					BuyRoom("Houses/argil_base.xml", mainObjects);

					Toasts::showAdvancedNotification("Property Purchased", "You are now the owner of ~COLOR_GOLD~Argil Rise cabin", "toast_log_blips", "blip_robbery_home", 200);

					MAP::REMOVE_BLIP(&housesBlip[7]);


					Houses[7] = 1;

				}


			}
		}

		if (distanceBetween(Misc::toVector3(-1791.772, -385.420, 160.329), playerPos) < 15.f) {
			test = MONEY::_MONEY_GET_CASH_BALANCE() + 5000 * 100;
			if (test <= current_cash) {
				if (!Houses[2]) {
					BuyRoom("Houses/shepherd_base.xml", mainObjects);

					Toasts::showAdvancedNotification("Property Purchased", "You are now the owner of ~COLOR_GOLD~Shepherds Rise cabin", "toast_log_blips", "blip_robbery_home", 200);

					MAP::REMOVE_BLIP(&housesBlip[2]);


					Houses[2] = 1;

				}


			}
		}

		if (distanceBetween(Misc::toVector3(-322.555, 801.826, 117.882), playerPos) < 15.f) {
			test = MONEY::_MONEY_GET_CASH_BALANCE() + 5000 * 100;
			if (test <= current_cash) {
				if (!Houses[1]) {
					BuyRoom("Houses/ridge_base.xml", mainObjects);

					Toasts::showAdvancedNotification("Property Purchased", "You are now the owner of ~COLOR_GOLD~Ridge View cabin", "toast_log_blips", "blip_robbery_home", 200);

					MAP::REMOVE_BLIP(&housesBlip[1]);


					Houses[1] = 1;

				}


			}
		}





		HUD::_UIPROMPT_SET_TEXT(PromptBuy, (char*)textLabel); //set text



		//TODO saint denis
		if (Houses[0]) {
			//OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(1555588463, 0);



		}




		if (Houses[1]) {
			OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(2188892390, 0);
			OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(2472180395, 0);


			//	PROPSET::_REQUEST_PROP_SET(MISC::GET_HASH_KEY("pg_player_campfire_add05x_bed"));
				//PROPSET::_CREATE_PROP_SET(MISC::GET_HASH_KEY("pg_player_campfire_add05x_bed"), 1781.169, 466.942, 113.038, 1, 1, 1, 1, 1);

			//	PROPSET::_REQUEST_PROP_SET(MISC::GET_HASH_KEY("pg_player_campfire_add01x"));
			//	PROPSET::_CREATE_PROP_SET(MISC::GET_HASH_KEY("pg_player_campfire_add01x"), 1777.253, 458.067, 112.494, 1, 1, 1, 1, 1);


		}
		else {
			OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(2188892390, 1);
			OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(2472180395, 1);
		}



		if (Houses[2]) {
			OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(3221874820, 0);
			OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(2366407202, 0);

			//PROPSET::_REQUEST_PROP_SET(MISC::GET_HASH_KEY("pg_player_campfire_add05x_bed"));
			//PROPSET::_CREATE_PROP_SET(MISC::GET_HASH_KEY("pg_player_campfire_add05x_bed"), -1552.026, 257.308, 114.799, 1, 1, 1, 1, 1);

			//PROPSET::_REQUEST_PROP_SET(MISC::GET_HASH_KEY("pg_player_campfire_add01x"));
			//PROPSET::_CREATE_PROP_SET(MISC::GET_HASH_KEY("pg_player_campfire_add01x"), -1557.876, 246.308, 113.899, 1, 1, 1, 1, 1);

		}
		else {
			OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(3221874820, 1);
			OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(2366407202, 1);
		}


		OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(1087218607, 0);
		if (Houses[3]) {
			//OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(1087218607, 0);

			//PROPSET::_REQUEST_PROPSET(MISC::GET_HASH_KEY("pg_player_campfire_add05x_bed"));
			//PROPSET::_CREATE_PROPSET(MISC::GET_HASH_KEY("pg_player_campfire_add05x_bed"), housesVecs[3].x + 2, housesVecs[3].y + 3, housesVecs[3].z, 1, 1, 1, 1, 1);

		}
		else {
			//OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(1087218607, 1);
		}


		if (Houses[4]) {
			OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(1562553736, 0);

		//	PROPSET::_REQUEST_PROPSET(MISC::GET_HASH_KEY("pg_player_campfire_add05x_bed"));
		//	PROPSET::_CREATE_PROPSET(MISC::GET_HASH_KEY("pg_player_campfire_add05x_bed"), housesVecs[4].x - 0.5f, housesVecs[4].y + 2, housesVecs[4].z, 1, 1, 1, 1, 1);

		}
		else {
			OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(1562553736, 1);
		}


		if (Houses[5]) {
			OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(2046695029, 0);

		//	PROPSET::_REQUEST_PROPSET(MISC::GET_HASH_KEY("pg_player_campfire_add05x_bed"));
		//	PROPSET::_CREATE_PROPSET(MISC::GET_HASH_KEY("pg_player_campfire_add05x_bed"), housesVecs[5].x - 0.5f, housesVecs[5].y + 2, housesVecs[5].z, 1, 1, 1, 1, 1);

		}
		else {
			OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(2046695029, 1);
		}

		if (Houses[6]) {
			OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(3693364451, 0);

			//PROPSET::_REQUEST_PROPSET(MISC::GET_HASH_KEY("pg_player_campfire_add05x_bed"));
			//PROPSET::_CREATE_PROPSET(MISC::GET_HASH_KEY("pg_player_campfire_add05x_bed"), housesVecs[6].x - 1.f, housesVecs[6].y + 2, housesVecs[6].z - 0.1, 1, 1, 1, 1, 1);


		}
		else {

			OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(3693364451, 1);
		}

		if (Houses[7]) {

			OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(3327934361, 0);
			OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(3014302262, 0);

		}
		else {
			OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(3327934361, 1);
			OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(3014302262, 1);
		}



		WAIT(0);
	}
}

void ScriptMain()
{	
	srand(GetTickCount());
	main();
}
