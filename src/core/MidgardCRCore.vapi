
[CCode (lower_case_cprefix = "midgard_cr_core_", cheader_filename = "midgard_cr_core.h")]

namespace MidgardCRCore {
	[Compact]
	public class Config {
		public static bool read_file (MidgardCR.Config config, string name, bool user) throws GLib.KeyFileError, GLib.FileError;
		public static bool read_file_at_path (MidgardCR.Config config, string path) throws GLib.KeyFileError, GLib.FileError;
		public static bool read_data (MidgardCR.Config config, string data) throws GLib.KeyFileError;
		public static string[]? list_files (bool user) throws GLib.KeyFileError;
		public static bool save_file (MidgardCR.Config config, string name, bool user) throws GLib.KeyFileError, GLib.FileError;
		public static bool save_file_at_path (MidgardCR.Config config, string path) throws GLib.KeyFileError, GLib.FileError;
		public static bool create_blobdir (MidgardCR.Config config) throws GLib.KeyFileError, GLib.FileError;
		public static string get_default_confdir ();
		public static void set_dbtype_id (MidgardCR.Config config, string dbtype);
	}

	public class StorageSQL {
		public static string create_query_insert_columns (GLib.Object object, MidgardCR.ObjectModel schema, MidgardCR.StorageModel model);
		public static string create_query_insert_values (GLib.Object object, MidgardCR.ObjectModel schema, MidgardCR.StorageModel model);
		public static string create_query_insert (GLib.Object object, MidgardCR.ObjectModel schema, MidgardCR.StorageModel model);
	}
	
	public class SQLStorageManager {
		public static bool open (MidgardCR.SQLStorageManager storage_mgr) throws MidgardCR.StorageManagerError;
		public static bool close (MidgardCR.SQLStorageManager storage_mgr) throws MidgardCR.StorageManagerError;
		public static bool initialize_storage (MidgardCR.SQLStorageManager storage_mgr) throws MidgardCR.StorageManagerError;
		public static bool table_exists (MidgardCR.SQLStorageManager manager, MidgardCR.SQLTableModel storage_model);
		public static void table_create (MidgardCR.SQLStorageManager manager, MidgardCR.SQLTableModel storage_model) throws MidgardCR.ExecutableError;
		public static void table_remove (MidgardCR.SQLStorageManager manager, MidgardCR.SQLTableModel storage_model) throws MidgardCR.ExecutableError;
		public static bool column_exists (MidgardCR.SQLStorageManager manager, MidgardCR.SQLColumnModel model);
		public static bool column_create (MidgardCR.SQLStorageManager manager, MidgardCR.SQLColumnModel model) throws MidgardCR.ExecutableError;
		public static bool column_update (MidgardCR.SQLStorageManager manager, MidgardCR.SQLColumnModel model) throws MidgardCR.ExecutableError;
		public static bool column_remove (MidgardCR.SQLStorageManager manager, MidgardCR.SQLColumnModel model) throws MidgardCR.ExecutableError;
		public static int query_execute (MidgardCR.SQLStorageManager manager, string query) throws MidgardCR.ExecutableError;
		public static void load_models (MidgardCR.SQLStorageManager storage_mgr) throws MidgardCR.StorageManagerError;
}

	public class SQLStorageModelManager {
		public static void prepare_create (MidgardCR.SQLStorageModelManager manager, MidgardCR.Model model) throws MidgardCR.ValidationError;
		public static void execute (MidgardCR.SQLStorageModelManager manager) throws MidgardCR.ExecutableError;
	}

	public class SQLStorageContentManager {
		public static void storable_insert (MidgardCR.Storable storable, MidgardCR.SQLStorageManager manager, MidgardCR.ObjectModel object_model, MidgardCR.SQLTableModel table_model) throws MidgardCR.StorageContentManagerError;
	}

	public class ObjectBuilder {
		public static void register_types (MidgardCR.ObjectBuilder builder) throws GLib.Error;
	}
}
