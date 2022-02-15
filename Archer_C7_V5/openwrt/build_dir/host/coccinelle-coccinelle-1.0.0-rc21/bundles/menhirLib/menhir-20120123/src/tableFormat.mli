module type TABLES =
  sig
    type token
    val token2terminal : token -> int
    val error_terminal : int
    val token2value : token -> Obj.t
    val default_reduction : PackedIntArray.t
    val error : int * string
    val action : PackedIntArray.t * PackedIntArray.t
    val lhs : PackedIntArray.t
    val goto : PackedIntArray.t * PackedIntArray.t
    val semantic_action : ((int, Obj.t, token) EngineTypes.env -> unit) array
    exception Error
    val recovery : bool
    val trace : (string array * string array) option
  end
