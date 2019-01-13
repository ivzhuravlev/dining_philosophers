function Component()
{
}

Component.prototype.createOperations = function()
{
	// component.createOperations();
	// component.addOperation("CreateShortcut", "@TargetDir@\\dining_philosophers.exe", "@DesktopDir@\\DiningPhilosophers.lnk",
              // "workingDirectory=@TargetDir@", "iconPath=@TargetDir@\\dining_philosophers.exe",
              // "iconId=1", "description=Start application");
			  
	try {
        // call the base create operations function
        component.createOperations();
        if (installer.value("os") == "win") { 
            try {
                var userProfile = installer.environmentVariable("USERPROFILE");
                installer.setValue("UserProfile", userProfile);
                component.addOperation("CreateShortcut", "@TargetDir@\\dining_philosophers.exe", "@UserProfile@\\Desktop\\DiningPhilosophers.lnk");
            } catch (e) {
                // Do nothing if key doesn't exist
            }
        }
    } catch (e) {
        print(e);
    }
}
	