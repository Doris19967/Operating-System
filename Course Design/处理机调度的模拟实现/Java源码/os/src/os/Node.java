/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package os;

/**
 *
 * @author Administrator
 */
public class Node {
    String name;
    int priority;//优先级
    int runtime;//服务时间
    int arrivaltime;//到达时间
    int starttime;//开始时间
    int endtime;//结束时间
    int turntime;  //周转时间=结束时间-到达时间
    double dturntime;  //带权周转时间=周转时间/服务时间
    Node nextnode;
    int statu;
    int newarrival;
    int newruntime;//新的运行时间

    //初始化节点，即进程
    public Node(String name,int priority,int runtime,int arrivaltime, int starttime, int endtime, int turntime, double dturntime){
        this.name = name;
        this.priority = priority;
        this.runtime = runtime;
        this.arrivaltime = arrivaltime;
        this.nextnode = null;
        this.starttime = starttime;
        this.endtime = endtime;
        this.turntime = turntime;
        this.dturntime = dturntime;
        this.newarrival = arrivaltime;
        this.newruntime = runtime;
    }
    public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getPriority() {
		return priority;
	}

	public void setPriority(int priority) {
		this.priority = priority;
	}

	public int getRuntime() {
		return runtime;
	}

	public void setRuntime(int runtime) {
		this.runtime = runtime;
	}

	public int getArrivaltime() {
		return arrivaltime;
	}

	public void setArrivaltime(int arrivaltime) {
		this.arrivaltime = arrivaltime;
	}

	public int getStarttime() {
		return starttime;
	}

	public void setStarttime(int starttime) {
		this.starttime = starttime;
	}

	public int getEndtime() {
		return endtime;
	}

	public void setEndtime(int endtime) {
		this.endtime = endtime;
	}

	public int getTurntime() {
		return turntime;
	}

	public void setTurntime(int turntime) {
		this.turntime = turntime;
	}

	public double getDturntime() {
		return dturntime;
	}

	public void setDturntime(double dturntime) {
		this.dturntime = dturntime;
	}

	public Node getNextnode() {
		return nextnode;
	}

	public void setNextnode(Node nextnode) {
		this.nextnode = nextnode;
	}

	public int getStatu() {
		return statu;
	}

	public void setStatu(int statu) {
		this.statu = statu;
	}

	public int getNewarrival() {
		return newarrival;
	}

	public void setNewarrival(int newarrival) {
		this.newarrival = newarrival;
	}

	public int getNewruntime() {
		return newruntime;
	}

	public void setNewruntime(int newruntime) {
		this.newruntime = newruntime;
	}

	public Node(String name, int priority, int runtime, int arrivaltime) {
		super();
		this.name = name;
		this.priority = priority;
		this.runtime = runtime;
		this.arrivaltime = arrivaltime;
	}

	public Node() {
		super();
	}
}
