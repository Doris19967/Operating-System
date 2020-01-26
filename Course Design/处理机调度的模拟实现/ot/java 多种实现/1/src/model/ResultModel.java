package model;

import javafx.beans.property.FloatProperty;
import javafx.beans.property.IntegerProperty;
import javafx.beans.property.SimpleFloatProperty;
import javafx.beans.property.SimpleIntegerProperty;

/**
 * 
 * ClassName: ResultModel 
 * @Description: 调度结果的JavaBean
 * @author Mr_blue
 * @date 2017年6月28日
 */
public class ResultModel {
	private PCB pcb;
	private IntegerProperty pid;   
	private IntegerProperty cpuid;
	private IntegerProperty status;
	private IntegerProperty priority;
	private FloatProperty serverTime;
	private FloatProperty arriveTime;
	private FloatProperty needTime;
	private FloatProperty startTime;
	private FloatProperty finishTime;
	private FloatProperty turnaroundTime;
	private FloatProperty rturnaroundTime;
	private final String[] agrs= {"就绪","运行","完成","等待"};
	
	public ResultModel(PCB pcb,int pid,int status,int priority,float serverTime,
			float arriveTime,float needTime,float startTime,float finishTime,
			float turnaroundTime,float rturnaroundTime){
		
		this.pcb = pcb;
		this.pid = new SimpleIntegerProperty(pid);
		this.status = new SimpleIntegerProperty(status);
		this.priority = new SimpleIntegerProperty(priority);
		this.serverTime = new SimpleFloatProperty(serverTime);
		this.arriveTime = new SimpleFloatProperty(arriveTime);
		this.needTime = new SimpleFloatProperty(needTime);
		this.startTime = new SimpleFloatProperty(startTime);
		this.finishTime = new SimpleFloatProperty(finishTime);
		this.turnaroundTime = new SimpleFloatProperty(turnaroundTime);
		this.rturnaroundTime = new SimpleFloatProperty(rturnaroundTime);
	}
	public ResultModel(){
		this.pid = new SimpleIntegerProperty();
		this.cpuid = new SimpleIntegerProperty();
		this.status = new SimpleIntegerProperty();
		this.priority = new SimpleIntegerProperty();
		this.serverTime = new SimpleFloatProperty();
		this.arriveTime = new SimpleFloatProperty();
		this.needTime = new SimpleFloatProperty();
		this.startTime = new SimpleFloatProperty();
		this.finishTime = new SimpleFloatProperty();
		this.turnaroundTime = new SimpleFloatProperty();
		this.rturnaroundTime = new SimpleFloatProperty();
	}
	public PCB getPcb() {
		return pcb;
	}
	public void setPcb(PCB pcb) {
		this.pcb = pcb;
	}
	public int getPid() {
        return pid.get();
    }

    public IntegerProperty pidProperty() {
        return pid;
    }
    public void setPid(int pid) {
        this.pid.set(pid);
    }
    
    public int getCupid() {
        return cpuid.get();
    }

    public IntegerProperty cpuidProperty() {
        return cpuid;
    }
    public void setCupid(int cupid) {
        this.cpuid.set(cupid);
    }
    public int getStatus(){
    	return status.get();
    }
    public void setStatus(int status){
        this.status.set(status);	
    }
    public IntegerProperty statusProperty(){
    	return status;
    }
    public String getStatusString() {
        return agrs[getStatus()];
    }
    public void setPriority(int priority){
    	this.priority.set(priority);
    }
    public IntegerProperty priorityProperty(){
    	return priority;
    }
    public int getPriority(){
    	return priority.get();
    }
    public float getServerTime() {
        return serverTime.get();
    }
    public FloatProperty serverTimeProperty() {
        return serverTime;
    }
    public void setServerTime(float serverTime) {
        this.serverTime.set(serverTime);
    }
    
	public float getStartTime() {
        return startTime.get();
    }
    public FloatProperty startTimeProperty() {
        return startTime;
    }
    
    public void setStartTime(float startTime) {
        this.startTime.set(startTime);
    }
    
    public float getArriveTime() {
        return arriveTime.get();
    }
    public FloatProperty arriverTimeProperty() {
        return arriveTime;
    }
    
    public void setArriveTime(float arriveTime) {
        this.arriveTime.set(arriveTime);
    }
    
    public float getNeedTime() {
        return needTime.get();
    }
    public FloatProperty needTimeProperty() {
        return needTime;
    }
    public void setNeedTime(float needTime) {
        this.needTime.set(needTime);
    }
    public float getFinishTime() {
        return finishTime.get();
    }

    public FloatProperty finishTimeProperty() {
        return finishTime;
    }

    public void setFinishTime(float finishTime) {
        this.finishTime.set(finishTime);
    }

    public float getTurnaroundTime() {
        return turnaroundTime.get();
    }

    public FloatProperty turnaroundTimeProperty() {
        return turnaroundTime;
    }

    public void setTurnaroundTime(float turnaroundTime) {
        this.turnaroundTime.set(turnaroundTime);
    }

    public float getRturnaroundTime() {
        return rturnaroundTime.get();
    }

    public FloatProperty rturnaroundTimeProperty() {
        return rturnaroundTime;
    }

    public void setRturnaroundTime(float rturnaroundTime) {
        this.rturnaroundTime.set(rturnaroundTime);
    }
}