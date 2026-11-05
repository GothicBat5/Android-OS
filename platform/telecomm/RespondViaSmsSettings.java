package com.android.server.telecom;

import android.app.ActionBar;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.EditTextPreference;
import android.preference.Preference;
import android.preference.PreferenceActivity;
import android.preference.PreferenceScreen;
import android.telecom.Log;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.MenuItem;
import android.widget.Button;

public class RespondViaSmsSettings extends PreferenceActivity implements Preference.OnPreferenceChangeListener 
{
    private SharedPreferences mPrefs;
    @Override
    protected void onCreate(Bundle icicle) 
    {
        super.onCreate(icicle);
        Log.d(this, "Settings: onCreate()...");

        QuickResponseUtils.maybeMigrateLegacyQuickResponses(this);
        getPreferenceManager().setSharedPreferencesName(QuickResponseUtils.SHARED_PREFERENCES_NAME);
        mPrefs = getPreferenceManager().getSharedPreferences();
        QuickResponseUtils.maybeResetQuickResponses(this, mPrefs);
    }
    @Override
    public void onResume() 
    {
        super.onResume();
        PreferenceScreen preferenceScreen = getPreferenceScreen();
        if (preferenceScreen != null) {
            preferenceScreen.removeAll();
        }

        addPreferencesFromResource(R.xml.respond_via_sms_settings);
        initPref(findPreference(QuickResponseUtils.KEY_CANNED_RESPONSE_PREF_1));
        initPref(findPreference(QuickResponseUtils.KEY_CANNED_RESPONSE_PREF_2));
        initPref(findPreference(QuickResponseUtils.KEY_CANNED_RESPONSE_PREF_3));
        initPref(findPreference(QuickResponseUtils.KEY_CANNED_RESPONSE_PREF_4));
        ActionBar actionBar = getActionBar();
      
        if (actionBar != null) 
        {
            // android.R.id.home will be triggered in onOptionsItemSelected()
            actionBar.setDisplayHomeAsUpEnabled(true);
            // set the talkback voice prompt to "Back" instead of "Navigate Up"
            actionBar.setHomeActionContentDescription(R.string.back);
        }
    }
    // Preference.OnPreferenceChangeListener implementation
    @Override
    public boolean onPreferenceChange(Preference preference, Object newValue) 
    {
        Log.d(this, "onPreferenceChange: key = %s", preference.getKey());
        Log.d(this, "  preference = '%s'", preference);
        Log.d(this, "  newValue = '%s'", newValue);
        EditTextPreference pref = (EditTextPreference)findPreference(preference.getKey());

        if (((String) newValue).length() != 0) 
        {
            pref.setTitle((String) newValue);
            // Save the new preference value.
            SharedPreferences.Editor editor = mPrefs.edit();
            editor.putString(pref.getKey(), (String) newValue).commit();
        }
        // If the user just reset the quick response to its original text, clear the pref.
        QuickResponseUtils.maybeResetQuickResponses(this, mPrefs);
        return true;  // means it's OK to update the state of the Preference with the new value
    }
    @Override
    public boolean onOptionsItemSelected(MenuItem item) 
    {
        final int itemId = item.getItemId();
        
        switch (itemId) 
        {
            case android.R.id.home:
                goUpToTopLevelSetting(this);
                return true;
            default:
        }
        return super.onOptionsItemSelected(item);
    }
    /**
     * Finish current Activity and go up to the top level Settings.
     */
    public static void goUpToTopLevelSetting(Activity activity) {
        activity.finish();
    }
    /**
     * Initialize the preference to the persisted preference value or default text.
     */
    private void initPref(Preference preference) 
    {
        EditTextPreference pref = (EditTextPreference) preference;
        pref.setText(mPrefs.getString(pref.getKey(), pref.getText()));
        pref.setTitle(pref.getText());
        pref.getEditText().addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {
            }
            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
            }
            @Override
            public void afterTextChanged(Editable s) {
                try {
                    Button button = ((AlertDialog) pref.getDialog())
                            .getButton(AlertDialog.BUTTON_POSITIVE);
                    if (s.toString().length() == 0) {
                        button.setEnabled(false);
                    } 
                    else {
                        button.setEnabled(true);
                    }
                } 
                catch (NullPointerException e) 
                {
                    Log.d(this, e.toString());
                }
            }
        });
        pref.setOnPreferenceChangeListener(this);
    }
}
