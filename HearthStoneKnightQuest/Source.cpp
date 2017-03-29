#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <cstdlib> 
#include <ctime>

using namespace std;

class Evolve {
public:
	Evolve() {}
	Evolve(string name, int score, int s, bool wb) :evolveName(name), evolveScore(score), serial(s), wordbuf(wb) {}
	int serial;
	string evolveName;
	int evolveScore;
	bool wordbuf;
	inline bool operator< (const Evolve& rhs) { return this->evolveName < rhs.evolveName; }
};

class OurBoss
{
public:
	OurBoss() {};
	OurBoss(vector<Evolve>& Evolve5Times);
	string combined_string;
	string print_string;
	int final_score;
	int total_damage;
	int life;
	int damage;
	int count;
	inline bool operator< (const OurBoss& rhs) { return this->final_score < rhs.final_score; }
};

OurBoss::OurBoss(vector<Evolve>& Evolve5Times) {
	life = 5; damage = 5; final_score = 0; total_damage = 0; count = 0;
	sort(Evolve5Times.begin(), Evolve5Times.end());
	combined_string = ""; print_string = "";
	for (int i = 0; i < Evolve5Times.size(); i++)
	{
		combined_string += Evolve5Times[i].evolveName;
		if (!Evolve5Times[i].wordbuf)
		{
			if (Evolve5Times[i].evolveName == "3��")damage += 3;
			if (Evolve5Times[i].evolveName == "3Ѫ")life += 3;
			if (Evolve5Times[i].evolveName == "11") { damage += 1; life += 1; }
		}
		else {
			print_string += Evolve5Times[i].evolveName;
			
		}
	}
	total_damage = damage;
	for (int i = 0; i < Evolve5Times.size(); i++)if (Evolve5Times[i].evolveName == "��ŭ") { total_damage *= 2;  break; }
	for (int i = 0; i < Evolve5Times.size(); i++)if (Evolve5Times[i].evolveName == "Ǳ��") 
	{ 
		for (int j = 0; j < Evolve5Times.size(); j++)
		{
			if (Evolve5Times[j].evolveName == "ħ��")Evolve5Times[j].evolveScore -= 2;
		}
		final_score += 90; break; 
	}
	final_score += total_damage * 2;
	final_score += life;
	for (int i = 0; i < Evolve5Times.size(); i++) { if (Evolve5Times[i].wordbuf)final_score += Evolve5Times[i].evolveScore; }
	//for (int i = 0; i < Evolve5Times.size(); i++){ final_score += ; break; }

	print_string += to_string(damage) + "/" + to_string(life);
}

int main()
{
	

	
	time_t t; time(&t);
	srand(t);
	vector<OurBoss> bosses;
	vector<Evolve> eSet;//Evolve Set
	for (int cnt = 0; cnt < 100000; cnt++) 
	{
		eSet.clear();
		eSet.push_back(Evolve("Ǳ��", 10, 1, true));
		eSet.push_back(Evolve("��ŭ", 9, 2, true));
		eSet.push_back(Evolve("3��", 7, 3, false));
		eSet.push_back(Evolve("ʥ��", 6, 4, true));
		eSet.push_back(Evolve("ħ��", 5, 5, true));
		eSet.push_back(Evolve("11", 4, 6, false));
		eSet.push_back(Evolve("3Ѫ", 2, 7, false));
		eSet.push_back(Evolve("����", 1, 8, true));
		eSet.push_back(Evolve("�綾", 0, 9, true));
		eSet.push_back(Evolve("����", -1, 10, true));
		vector<Evolve> Evolve5Times;

		for (int i = 0; i < 5; i++)//Evolve 5 times
		{
			random_shuffle(eSet.begin(), eSet.end());
			int max_idx = 0; int max_score = -100;
			for (int j = 0; j < 3; j++) {
				//cout << eSet[j].evolveName << " ";
				if (eSet[j].evolveScore > max_score)
				{
					max_idx = j;
					max_score = eSet[j].evolveScore;
				}
			}
			//cout << " Choose: " << eSet[max_idx].evolveName << endl;
			if (eSet[max_idx].wordbuf)eSet[max_idx].evolveScore -= 20;
			//if max_idx is Ǳ��, minus ħ��'s score by 2
			if (eSet[max_idx].serial == 1) { for (int k = 0; k < eSet.size(); k++) { if (eSet[k].serial == 5) { eSet[k].evolveScore -= 2; } } }
			//if max_idx is ħ��, minus Ǳ��'s score by 2
			if (eSet[max_idx].serial == 5) { for (int k = 0; k < eSet.size(); k++) { if (eSet[k].serial == 1) { eSet[k].evolveScore -= 2; } } }
			Evolve5Times.push_back(eSet[max_idx]);
		}
		OurBoss boss(Evolve5Times); bool found = false;
		for (int i = 0; i < bosses.size(); i++)
		{
			if (boss.combined_string == bosses[i].combined_string) {
				bosses[i].count++; found = true; break;
			}
		}
		if (!found)bosses.push_back(boss);
	}/*
	
	for (int i = 0; i < bosses.size(); i++)
	{
		cout << bosses[i].combined_string << endl;
	}
*/
	sort(bosses.begin(), bosses.end());
	int total_ct = 0;
	for (int i = 0; i < bosses.size(); i++)
	{
		total_ct += bosses[i].count;
	}
	for (int i = 0; i < bosses.size(); i++)
	{
		cout << bosses[i].print_string << " "<<(float)bosses[i].count / (float)total_ct * 100 <<"%"<<endl;
	}
	cin >> eSet[0].evolveName;
}