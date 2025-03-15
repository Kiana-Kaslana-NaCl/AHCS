# Anti-Honkai Combat System

**AHCS_updatekiller:**

AHCS_updatekiller adopts a relatively elegant method to stop the Windows Update for 1000 years. Moreover, you can recover it anytime when you want to update Windows. It achieves a longer pause duration by overwriting the string of the pause update duration in the Windows registry. As of now (2025.03), the longest time we can write is 975 years (up to 3000.08.24).

The differences between release, beta and userdebug version:

- Release: the nominal version of AHCS program, running as the Administration permission.
- Beta: the high-permission version of the release, running as SYSTEM permission with the TrustedInstaller token.
- Userdebug: the debug version, you can see the running information, also running as SYSTEM permission with the TrustedInstaller token.

If you want to change it by yourself, you can try to create two files with the extension .reg in any directory of your local computer, use 'Windows Registry Editor Version 5.00' separately as the first line and add the following main registry data separately to the two files you create. And then, save the files and double-click them to add the registry data.

The main registry data:

[HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UX\Settings]:

"ActiveHoursEnd"=dword:00000003
"ActiveHoursStart"=dword:00000009
"AllowMUUpdateService"=dword:00000000
"PauseFeatureUpdatesStartTime"="2024-09-11T07:02:47Z"
"PauseFeatureUpdatesEndTime"="9999-08-24T07:02:47Z"
"PauseQualityUpdatesStartTime"="2024-09-11T07:02:47Z"
"PauseQualityUpdatesEndTime"="9999-08-24T07:02:47Z"
"PauseUpdatesStartTime"="2024-09-11T07:02:47Z"
"PauseUpdatesExpiryTime"="3000-08-24T07:02:47Z"

[HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsUpdate\UpdatePolicy\PolicyState]:

"DeferQualityUpdates"=dword:00000000
"DeferFeatureUpdates"=dword:00000000
"BranchReadinessLevel"="CB"
"IsDeferralIsActive"=dword:00000001
"IsWUfBConfigured"=dword:00000000
"IsWUfBDualScanActive"=dword:00000000
"UseUpdateClassPolicySource"=dword:00000000
"SetPolicyDrivenUpdateSourceForFeatureUpdates"=dword:ffffffff
"SetPolicyDrivenUpdateSourceForQualityUpdates"=dword:ffffffff
"SetPolicyDrivenUpdateSourceForDriverUpdates"=dword:ffffffff
"SetPolicyDrivenUpdateSourceForOtherUpdates"=dword:ffffffff
"TemporaryEnterpriseFeatureControlState"=dword:00000001
"PolicySources"=dword:00000010
"QualityUpdatesPaused"=dword:00000001
"QualityUpdatePausePeriodInDays"=dword:0005706a
"FeatureUpdatesPaused"=dword:00000001
"FeatureUpdatePausePeriodInDays"=dword:0005706a
"PauseFeatureUpdatesStartTime"="2024-09-11T07:02:47Z"
"PauseFeatureUpdatesEndTime"="9999-08-24T07:02:47Z"
"PauseQualityUpdatesStartTime"="2024-09-11T07:02:47Z"
"PauseQualityUpdatesEndTime"="9999-08-24T07:02:47Z"

未完待续
