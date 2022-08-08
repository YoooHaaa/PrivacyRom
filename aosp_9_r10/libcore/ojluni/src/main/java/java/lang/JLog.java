package java.lang;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class JLog {
    public static final String mTag = "Antiy-log";
    public static List mTagList;
    public static final int INFO = 4;
    public static final int ERROR = 6;
    public static native int println_native(int bufID, int priority, String tag, String msg);
    public static native int getpid();

    static {
        mTagList = new ArrayList();
        mTagList.add("Normal");  //0
        mTagList.add("Flow");    //1
        mTagList.add("Native");  //2
    }

    public static void print_info(int tag, String info) {
        try{
            i(mTag, "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++start");
            i(mTag, "Type:" + mTagList.get(tag));
            i(mTag, "Pid:" + getProcessID());
            i(mTag, info);
            i(mTag, "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++end\n");
        } catch (Exception e){
            showException(tag, e);
        }
    }

    public static void print_stack(int tag, String info) {
        try{
            i(mTag, "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++start");
            i(mTag, "Type:" + mTagList.get(tag));
            i(mTag, "Pid:" + getProcessID());
            i(mTag, info);
            i(mTag, "stackTrace:");
            i(mTag, getStackTrace());
            i(mTag, "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++end\n");
        } catch (Exception e){
            showException(tag, e);
        }
    }

    public static void print_stack(int tag, String info, Object extra) {
        try{
            i(mTag, "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++start");
            i(mTag, "Type:" + mTagList.get(tag));
            i(mTag, "PID:" + getProcessID());
            i(mTag, info);
            i(mTag, String.valueOf(extra));
            i(mTag, "stackTrace:");
            i(mTag, getStackTrace());
            i(mTag, "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++end\n");
        } catch (Exception e){
            showException(tag, e);
        }
    }

    public static String getStackTrace() {
        StringBuffer sb = new StringBuffer();
        try{
            Throwable ex = new Throwable();
            StackTraceElement[] stackElements = ex.getStackTrace();
            for (int i = 0; i < stackElements.length; i++) {
                StackTraceElement element = stackElements[i];
                sb.append("at " +
                        element.getClassName() +
                        "." +
                        element.getMethodName() +
                        "(" +
                        element.getFileName() +
                        ":" +
                        element.getLineNumber() +
                        ")\n");
            }
        } catch(Exception e){

        }
        return sb.toString();
    }

    public static void showException(int tag, Exception e){
        e(mTag, "---------------------------------------------------------start");
        e(mTag, "Tag:" + mTagList.get(tag));
        e(mTag, getExceptionLine());
        e(mTag, e.toString());
        e(mTag, "---------------------------------------------------------end\n");
    }

    public static String getExceptionLine(){
        StackTraceElement element = new Throwable().getStackTrace()[1];
        return element.getFileName() + "-->" + element.getLineNumber() + " : " + element.getClassName();
    }

    public static int getProcessID(){
        try{
            return getpid();
        } catch (Exception e){
        }
        return -1;
    }

    public static int i(String tag, String msg){
        return println_native(0, INFO, tag, msg);
    }
    public static int e(String tag, String msg){
        return println_native(0, ERROR, tag, msg);
    }
}
