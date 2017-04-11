#ifndef COMMONS_HPP
#define COMMONS_HPP

#define INF 99999999

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

//Total Weighted Tardiness Job-Shop Scheduling Problem
namespace twtjssp{

	enum NodeType{GHOST, BEGIN, INTERNO};
	enum EdgeType{CONJUNTIVO, DISJUNTIVO};
	
	// CONJUNCAO => e
	// DISJUNCAO => ou

	struct Schedule{
		int job;
		int task;
		int machine;
		int time_execution;

		Schedule(){
			machine = time_execution = -1;
			job = task = -1;
		}

		Schedule(int m, int t){
			machine = m;
			time_execution = t;
		}

		Schedule(int j, int t, int tm){
			job = j;
			task = t;
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

		Node(int j, int o, int i, NodeType tp){
			this->job = j;
			this->index = i;
			this->operation = o;
			this->type = tp;
		}

	};

	struct Edge{
		Node source;
		Node destination;
		int weight;
		int index;

		Edge(){
			weight = -1;
		}

		Edge(Node src, Node dest, int wght){
			this->source = src;
			this->destination = dest;
			this->weight = wght;
		}

		void invertWay(){
			Node aux = destination;
			destination = source;
			source = aux;
		}

	};

	struct Graph{
		int nVertex;
		int nEdges;

		vector<Edge> edges;
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

	typedef vector<vector<Schedule>> ScheduleMatrix;

	static bool compara_tempo(Schedule p1, Schedule p2) {
		return p1.time_execution < p2.time_execution;
	}

	static bool compara_task(Schedule p1, Schedule p2){
		return p1.task < p2.task;
	}

	inline void print_schedule(Schedule s){
		cout << "(" << s.job << "," << s.task << "," << s.machine << "," << s.time_execution << ") - ";
	}
}

#endif