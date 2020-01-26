package model;

/**
 * 
 * ClassName: PCB 
 * @Description: 进程控制块，表示一个进程
 * @author Mr_blue
 * @date 2017年6月28日
 */

public class PCB {
	private int pid;
	private float arriveTime;
	private float serviceTime;
	private float startTime;
	private float finishTime;
	private float needTime;
	private float timeSlice;
	private int status;//0就绪，1运行，2完成,3等待
	private int priority;
	
	public int getPid() {
		return pid;
	}
	public void setPid(int PID) {
		this.pid = PID;
	}
	public float getArriveTime() {
		return arriveTime;
	}
	public void setArriveTime(float arriveTime) {
		this.arriveTime = arriveTime;
	}
	public float getServiceTime() {
		return serviceTime;
	}
	public void setServiceTime(float serviceTime) {
		this.serviceTime = serviceTime;
	}
	public float getStartTime() {
		return startTime;
	}
	public void setStartTime(float startTime) {
		this.startTime = startTime;
	}
	public float getFinishTime() {
		return finishTime;
	}
	public void setFinishTime(float finishTime) {
		this.finishTime = finishTime;
	}
	public int getState() {
		return status;
	}
	public void setState(int state) {
		this.status = state;
	}
	public int getPriority() {
		return priority;
	}
	public void setPriority(int priority) {
		this.priority = priority;
	}
	public float getNeedTime() {
		return needTime;
	}
	public void setNeedTime(float needTime) {
		this.needTime = needTime;
	}
	public float getTimeSlice() {
		return timeSlice;
	}
	public void setTimeSlice(float timeSlice) {
		this.timeSlice = timeSlice;
	}
	public int getStatus() {
		return status;
	}
	public void setStatus(int status) {
		this.status = status;
	}	
}

