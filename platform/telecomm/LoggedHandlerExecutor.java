package com.android.server.telecom;

import android.os.Handler;
import android.telecom.Logging.Runnable;
import java.util.concurrent.Executor;

/** An executor that starts a log session before executing a runnable */
public class LoggedHandlerExecutor implements Executor 
{
    private Handler mHandler;
    private String mSessionName;
    private TelecomSystem.SyncRoot mLock;
  
    public LoggedHandlerExecutor(Handler handler, String sessionName, TelecomSystem.SyncRoot lock) 
    {
        mHandler = handler;
        mSessionName = sessionName;
        mLock = lock;
    }
  
    @Override
    public void execute(java.lang.Runnable command) 
    {
        mHandler.post(new Runnable(mSessionName, mLock) 
        {
            @Override
            public void loggedRun() 
            {
                command.run();
            }
        }.prepare());
    }
}
