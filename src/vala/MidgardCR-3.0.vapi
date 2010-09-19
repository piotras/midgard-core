/* MidgardCR-3.0.vapi generated by valac 0.9.7.109-f873e, do not modify. */

[CCode (cprefix = "MidgardCR", lower_case_cprefix = "midgard_cr_")]
namespace MidgardCR {
	[CCode (cheader_filename = "midgard3.h")]
	public class Config : GLib.Object {
		public Config ();
		public MidgardCR.Config copy ();
		public static string[]? list_files (bool user) throws GLib.FileError;
		public bool read_configuration (string name, bool user) throws GLib.KeyFileError, GLib.FileError;
		public bool read_configuration_at_path (string path) throws GLib.KeyFileError, GLib.FileError;
		public bool read_data (string data) throws GLib.KeyFileError, GLib.FileError;
		public bool save_configuration (string name, bool user) throws GLib.KeyFileError, GLib.FileError;
		public bool save_configuration_at_path (string path) throws GLib.KeyFileError, GLib.FileError;
		public string authtype { get; set; }
		public string blobdir { get; set; }
		public string cachedir { get; set; }
		public string dbdir { get; set; }
		public string dbname { get; set; }
		public string dbpass { get; set; }
		public uint dbport { get; set; }
		public string dbtype { get; set; }
		public string dbuser { get; set; }
		public string host { get; set; }
		public string logfilename { get; set; }
		public string loglevel { get; set; }
		public string midgardpassword { get; set; }
		public string midgardusername { get; set; }
		public string sharedir { get; set; }
		public bool tablecreate { get; set; }
		public bool tableupdate { get; set; }
		public bool testunit { get; set; }
		public string vardir { get; set; }
	}
	[CCode (cheader_filename = "midgard3.h")]
	public abstract class DBObject : GLib.Object, MidgardCR.Storable {
		public DBObject ();
	}
	[CCode (cheader_filename = "midgard3.h")]
	public abstract class Metadata : GLib.Object, MidgardCR.Storable {
		public Metadata ();
		public abstract uint action { get; }
		public abstract MidgardCR.Timestamp created { get; }
		public abstract string parent { get; construct; }
		public abstract MidgardCR.Timestamp revised { get; }
	}
	[CCode (cheader_filename = "midgard3.h")]
	public class QueryProperty : GLib.Object, MidgardCR.QueryValueHolder {
		public QueryProperty ();
	}
	[CCode (cheader_filename = "midgard3.h")]
	public class QueryValue : GLib.Object, MidgardCR.QueryValueHolder {
		public QueryValue ();
	}
	[CCode (cheader_filename = "midgard3.h")]
	public class SQLStorageManager : GLib.Object, MidgardCR.StorageManager {
		protected GLib.Object _cnc;
		protected GLib.Object _parser;
		public SQLStorageManager (string name, MidgardCR.Config config);
		public MidgardCR.Config config { get; construct; }
		public string name { get; construct; }
	}
	[CCode (cheader_filename = "midgard3.h")]
	public class SQLWorkspaceManager : MidgardCR.StorageWorkspaceManager, MidgardCR.SQLStorageManager {
		public SQLWorkspaceManager (string name, MidgardCR.Config config);
		public bool workspace_create (MidgardCR.WorkspaceStorage workspace) throws MidgardCR.WorkspaceStorageError;
		public bool workspace_exists (MidgardCR.WorkspaceStorage workspace) throws MidgardCR.WorkspaceStorageError;
	}
	[CCode (cheader_filename = "midgard3.h")]
	public class SchemaBuilder : GLib.Object, MidgardCR.Executable {
		public SchemaBuilder ();
		public MidgardCR.Storable? factory (MidgardCR.StorageManager storage, string classname) throws MidgardCR.SchemaBuilderError, MidgardCR.ValidationError;
		public MidgardCR.SchemaModel? get_schema_model (string classname);
		public void register_model (MidgardCR.SchemaModel model) throws MidgardCR.SchemaBuilderError, MidgardCR.ValidationError;
		public void register_storage_models (MidgardCR.StorageManager manager) throws MidgardCR.SchemaBuilderError, MidgardCR.ValidationError;
	}
	[CCode (cheader_filename = "midgard3.h")]
	public class SchemaModel : GLib.Object, MidgardCR.Model {
		public SchemaModel ();
		public MidgardCR.Model add_parent_model (MidgardCR.Model model);
		public string get_name ();
		public MidgardCR.Model? get_parent_model ();
		public bool is_valid ();
	}
	[CCode (cheader_filename = "midgard3.h")]
	public class SchemaModelProperty : GLib.Object, MidgardCR.Model {
		public SchemaModelProperty ();
		public MidgardCR.Model add_parent_model (MidgardCR.Model model);
		public string get_name ();
		public string get_namespace ();
		public MidgardCR.Model? get_parent_model ();
		public bool is_valid ();
		public void set_description (string description);
		public bool set_namespace (string name);
		public void set_private (bool toggle);
		public void set_value_default (GLib.Value value);
		public void set_value_gtype (GLib.Type type);
		public void set_value_typename (string name);
	}
	[CCode (cheader_filename = "midgard3.h")]
	public abstract class SchemaObject : GLib.Object, MidgardCR.Storable {
		public SchemaObject ();
		public abstract GLib.Value get_property_value (string name);
		public abstract string[]? list_all_properties ();
		public abstract void set_property_value (string name, GLib.Value value);
		public string guid { get; }
		public uint id { get; }
		public MidgardCR.Metadata metadata { get; }
	}
	[CCode (cheader_filename = "midgard3.h")]
	public abstract class Timestamp : GLib.Object {
		public Timestamp ();
	}
	[CCode (cheader_filename = "midgard3.h")]
	public class Workspace : GLib.Object, MidgardCR.WorkspaceStorage {
		public Workspace ();
		public MidgardCR.Workspace? get_by_path ();
		public MidgardCR.Workspace[]? list_children ();
		public MidgardCR.WorkspaceContext context { get; }
		public MidgardCR.Workspace parent { get; set; }
	}
	[CCode (cheader_filename = "midgard3.h")]
	public class WorkspaceContext : GLib.Object, MidgardCR.WorkspaceStorage {
		public WorkspaceContext ();
		public MidgardCR.Workspace? get_workspace_by_name ();
		public string[]? get_workspace_names ();
		public bool has_workspace (MidgardCR.Workspace workspace);
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface Executable {
		public abstract bool execute ();
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface Model : GLib.Object {
		public abstract MidgardCR.Model add_model (MidgardCR.Model model);
		public abstract MidgardCR.Model? get_model_by_name (string name);
		public abstract MidgardCR.ModelReflector get_reflector ();
		public abstract MidgardCR.Model[]? list_models ();
		public abstract string name { get; set; }
		public abstract string @namespace { get; set; }
		public abstract MidgardCR.Model parent { get; set; }
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface ModelProperty : MidgardCR.Model, MidgardCR.Executable {
		public abstract string description { get; set; }
		public abstract bool is_private { get; set; }
		public abstract GLib.Value value_default { get; set; }
		public abstract GLib.Type value_gtype { get; set; }
		public abstract string value_typename { get; set; }
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface ModelPropertyReflector : MidgardCR.ModelReflector {
		public abstract GLib.Value get_default_value ();
		public abstract string? get_description ();
		public abstract GLib.Type get_gtype ();
		public abstract string get_typename ();
		public abstract bool is_private ();
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface ModelReflector : GLib.Object {
		public abstract MidgardCR.Model model { get; construct; }
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface NamespaceManager : GLib.Object {
		public abstract bool create_uri (string uri, string name) throws MidgardCR.NamespaceManagerError;
		public abstract string get_name_by_uri (string uri);
		public abstract string get_uri_by_name (string name);
		public abstract string[]? list_names ();
		public abstract bool name_exists ();
		public abstract bool uri_exists ();
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface Profiler : GLib.Object {
		public abstract void enable (bool toggle);
		public abstract void end ();
		public abstract string get_execution_command ();
		public abstract int get_time ();
		public abstract void start ();
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface QueryConstraint : MidgardCR.QueryConstraintSimple {
		public abstract MidgardCR.QueryValueHolder holder { get; set; }
		public abstract string operator { get; set; }
		public abstract MidgardCR.QueryProperty property { get; set; }
		public abstract MidgardCR.QueryStorage storage { get; set; }
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface QueryConstraintGroup : MidgardCR.QueryConstraintSimple {
		public abstract void add_constraint (MidgardCR.QueryConstraintSimple constraint);
		public abstract string get_group_type ();
		public abstract void set_group_type (string name);
		public abstract string grouptype { get; set; }
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface QueryConstraintSimple : GLib.Object {
		public abstract MidgardCR.QueryConstraintSimple[]? list_constraints ();
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface QueryData : MidgardCR.QueryExecutor {
		public abstract void add_join (string type, MidgardCR.QueryProperty left_property, MidgardCR.QueryProperty right_property);
		public abstract void collect_property (MidgardCR.QueryProperty property, MidgardCR.QueryStorage storage);
		public abstract void list_data ();
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface QueryExecutor : MidgardCR.Executable {
		public abstract void add_order (MidgardCR.QueryProperty property, string type);
		public abstract uint get_results_count ();
		public abstract void set_constraint (MidgardCR.QueryConstraintSimple constraint);
		public abstract void set_limit (uint limit);
		public abstract void set_offset (uint offset);
		public abstract void validate () throws MidgardCR.ValidationError;
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface QueryManager : GLib.Object {
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface QuerySelect : MidgardCR.QueryExecutor {
		public abstract void add_join (string type, MidgardCR.QueryProperty left_property, MidgardCR.QueryProperty right_property);
		public abstract MidgardCR.Storable[]? list_objects ();
		public abstract void toggle_read_only (bool toggle);
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface QueryStorage : GLib.Object {
		public abstract string classname { get; set; }
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface QueryValueHolder : GLib.Object {
		public abstract GLib.Value get_value ();
		public abstract void set_value (GLib.Value value);
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface Storable : GLib.Object {
		public signal void create ();
		public signal void created ();
		public signal void remove ();
		public signal void removed ();
		public signal void update ();
		public signal void updated ();
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface StorageContentManager : GLib.Object {
		public abstract bool create (MidgardCR.Storable object) throws MidgardCR.StorageContentManagerError;
		public abstract bool exists (MidgardCR.Storable object);
		public abstract MidgardCR.QueryManager get_query_manager ();
		public abstract MidgardCR.StorageManager get_storage_manager ();
		public abstract bool purge (MidgardCR.Storable object) throws MidgardCR.StorageContentManagerError;
		public abstract bool remove (MidgardCR.Storable object) throws MidgardCR.StorageContentManagerError;
		public abstract bool save (MidgardCR.Storable object) throws MidgardCR.StorageContentManagerError;
		public abstract bool update (MidgardCR.Storable object) throws MidgardCR.StorageContentManagerError;
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface StorageExecutor : MidgardCR.Executable {
		public abstract bool exists ();
		public abstract void prepare_create () throws MidgardCR.ValidationError;
		public abstract void prepare_purge () throws MidgardCR.ValidationError;
		public abstract void prepare_remove () throws MidgardCR.ValidationError;
		public abstract void prepare_save () throws MidgardCR.ValidationError;
		public abstract void prepare_update () throws MidgardCR.ValidationError;
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface StorageManager : GLib.Object {
		public abstract MidgardCR.StorageManager clone ();
		public abstract bool close () throws MidgardCR.StorageManagerError;
		public abstract MidgardCR.StorageManager fork ();
		public abstract bool open () throws MidgardCR.StorageManagerError;
		public abstract MidgardCR.StorageContentManager content_manager { get; }
		public abstract MidgardCR.StorageModelManager model_manager { get; }
		public abstract MidgardCR.Profiler profiler { get; }
		public abstract MidgardCR.Transaction transaction { get; }
		public abstract MidgardCR.StorageWorkspaceManager workspace_manager { get; }
		public signal void closed ();
		public signal void opened ();
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface StorageManagerPool : GLib.Object {
		public abstract MidgardCR.StorageManager create_manager (string classname, string name);
		public abstract MidgardCR.StorageManager? get_manager_by_name (string name);
		public abstract string[]? list_managers ();
		public abstract void register_manager_type (string classname);
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface StorageModel : MidgardCR.Model {
		public abstract string location_get ();
		public abstract bool location_set (string location) throws MidgardCR.StorageModelError;
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface StorageModelManager : MidgardCR.Model, MidgardCR.StorageExecutor {
		public abstract MidgardCR.StorageModel create_storage_model (MidgardCR.SchemaModel schema_model, string location);
		public abstract MidgardCR.StorageModel? get_model_by_name (string name);
		public abstract MidgardCR.SchemaModel? get_schema_model_by_name (string name);
		public abstract MidgardCR.SchemaModel[]? list_schema_models ();
		public abstract MidgardCR.StorageModel[]? list_storage_models ();
		public abstract MidgardCR.NamespaceManager namespace_manager { get; }
		public abstract MidgardCR.StorageManager storage_manager { get; }
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface StorageModelProperty : MidgardCR.StorageExecutor, MidgardCR.ModelProperty {
		public abstract bool has_index ();
		public abstract bool is_primary ();
		public abstract string location_get ();
		public abstract bool location_set (string location);
		public abstract void set_index (bool toggle);
		public abstract void set_primary (bool toggle);
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface StorageWorkspaceManager : MidgardCR.StorageManager {
		public abstract MidgardCR.WorkspaceStorage workspace { get; set; }
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface Transaction : GLib.Object, MidgardCR.Executable {
		public abstract bool begin ();
		public abstract bool get_status ();
		public abstract bool rollback ();
		public abstract string name { get; construct; }
	}
	[CCode (cheader_filename = "midgard3.h")]
	public interface WorkspaceStorage : GLib.Object {
		public abstract string path { get; construct; }
	}
	[CCode (cprefix = "MIDGARD_CR_NAMESPACE_MANAGER_ERROR_", cheader_filename = "midgard3.h")]
	public errordomain NamespaceManagerError {
		URI_INVALID,
		URI_EXISTS,
		ALIAS_INVALID,
		ALIAS_EXISTS,
	}
	[CCode (cprefix = "MIDGARD_CR_SCHEMA_BUILDER_ERROR_", cheader_filename = "midgard3.h")]
	public errordomain SchemaBuilderError {
		NAME_EXISTS,
	}
	[CCode (cprefix = "MIDGARD_CR_STORAGE_CONTENT_MANAGER_ERROR_", cheader_filename = "midgard3.h")]
	public errordomain StorageContentManagerError {
		OBJECT_INVALID,
		OBJECT_DUPLICATE,
		INTERNAL,
	}
	[CCode (cprefix = "MIDGARD_CR_STORAGE_MANAGER_ERROR_", cheader_filename = "midgard3.h")]
	public errordomain StorageManagerError {
		ACCESS_DENIED,
	}
	[CCode (cprefix = "MIDGARD_CR_STORAGE_MODEL_ERROR_", cheader_filename = "midgard3.h")]
	public errordomain StorageModelError {
		STORAGE_INVALID,
		STORAGE_EXISTS,
		INTERNAL,
	}
	[CCode (cprefix = "MIDGARD_CR_VALIDATION_ERROR_", cheader_filename = "midgard3.h")]
	public errordomain ValidationError {
		NAME_INVALID,
		TYPE_INVALID,
		VALUE_INVALID,
		REFERENCE_INVALID,
		PARENT_INVALID,
		LOCATION_INVALID,
	}
	[CCode (cprefix = "MIDGARD_CR_WORKSPACE_STORAGE_ERROR_", cheader_filename = "midgard3.h")]
	public errordomain WorkspaceStorageError {
		WORKSPACE_STORAGE_ERROR_NAME_EXISTS,
		WORKSPACE_STORAGE_ERROR_INVALID_PATH,
		WORKSPACE_STORAGE_ERROR_OBJECT_NOT_EXISTS,
		WORKSPACE_STORAGE_ERROR_CONTEXT_VIOLATION,
	}
}
