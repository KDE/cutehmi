/**
  Project cloner.

  To make the project clonable it must use one of the cutehmi.ProjectGroup items (cutehmi.ToolProject or cutehmi.ExtensionProject),
  which provide extra `groupName` property.

  Files which are going to be copied must be referenced in one of the products belonging to the project group.

  Files tagged with 'cutehmi.clone.exclude' won't be cloned.

  To clone the project set Qbs `modules.cutehmi.clone.projects` property according to the pattern:
  `modules.cutehmi.clone.projects:<old project>,<new project>`. For example to clone Templates.CppPluginSkeleton.0 into
  My.Extension.0 set following:

  ```
  modules.cutehmi.clone.projects:Templates.CppPluginSkeleton.0,My.Extension.0
  ```

  Note that most of the product-specific elements such as export macros, namespaces, etc are currently not refactored automatically.
  */
Module {
	readonly property bool enabled: oldProject !== undefined && newProject !== undefined

	property stringList projects: undefined

	property string oldProject: projects !== undefined ? projects[0] : undefined

	property string newProject: projects !== undefined ? projects[1] : undefined
}
