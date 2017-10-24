#ifndef COMMONS_HPP
#define COMMONS_HPP

#define INF 99999999

#define GHOSTNODES 2
#define INITNODE 1

#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <functional>

using namespace std;

//Total Weighted Tardiness Job-Shop Scheduling Problem
namespace twtjssp{

	enum NodeType{GHOST, BEGIN, INTERNO};
	enum EdgeType{CONJUNTIVO, DISJUNTIVO};
	
	// CONJUNCAO => e
	// DISJUNCAO => ou

	struct Schedule{
		int job;
		int task, operation;
		int machine;
		int time_execution;

		Schedule(){
			machine = time_execution = -1;
			job = task = operation = -1;
		}

		Schedule(int m, int t){
			machine = m;
			time_execution = t;
		}

		Schedule(int j, int t, int m){
			job = j;
			task = operation = t;
			machine = m;
		}

/*		Schedule(int j, int t, int tm){
			job = j;
			task = t;
			time_execution = tm;
		}*/

		Schedule(int j, int t, int m, int tm){
			job = j;
			operation = task = t;
			machine = m;
			time_execution = tm;
		}
	};
	
	struct Node{
		int job;
		int operation;
		int index;
		NodeType type;

		Node(){
			job = operation = -1;
		}

		Node(int job, int op, int id, NodeType tp){
			this->job = job;
			this->index = id;
			this->operation = op;
			this->type = tp;
		}

		string toString(){
			stringstream ss;
			ss << "(" << job << "-" << operation << ": " << index << ")";
			return ss.str();
		}

	};

	struct EdgeData{
		int weight;
		bool critical;

		EdgeData(){
			weight = -1;
			critical = false;
		}

		EdgeData(int w, bool c){
			weight = w;
			critical = c;
		}

		bool isCritical(){
			return critical;
		}
	};

	struct Edge{
		Node source;
		Node destination;
		EdgeData data;
		int index;

		Edge(){
			
		}

		Edge(Node src, Node dest, int wght){
			this->source = src;
			this->destination = dest;
			/* this->weight = wght;
			this->critical = [&]() {
				if(source.job != destination.job && source.job != -1 && destination.job != -1) return true;
				return false;
			}(); */
		}

		void invertWay(){
			Node aux = destination;
			destination = source;
			source = aux;
		}

		string toString(){
			stringstream ss;
			//ss << source.toString() << " -> " << destination.toString() << " - " << weight << " " << index;
			return ss.str();
		}

	};

	struct JobTask{
		int job;	// as first
		int task;	// as second

		JobTask(int j, int t){
			this->job = j;
			this->task = t;
		}

		JobTask(){
			job = task = -1;
		}

		void print(){
			cout << "JobTask: Job: " << job;
			cout << " Task: " << task << endl;
		}
	};

	typedef vector< vector<Schedule> > ScheduleMatrix;
	typedef vector< vector<Schedule> > GanttRepresentation;

	static bool compara_tempo(Schedule p1, Schedule p2) {
		return p1.time_execution < p2.time_execution;
	}

	static bool compara_task(Schedule p1, Schedule p2){
		return p1.task < p2.task;
	}

	inline void print_schedule(Schedule s){
		cout << "(" << s.job << "," << s.task << "," << s.machine << "," << s.time_execution << ") - ";
	}

	inline float percent_between(float a, float b){
		return (((float)a/(float)b)-1)*100.f;
	}

	inline bool verify_critical(Schedule src, Schedule dest){
		if(src.job != dest.job && src.job != -1 && dest.job != -1) return true;

		return false;
	}
}

#endif