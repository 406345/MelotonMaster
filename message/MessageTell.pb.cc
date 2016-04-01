// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MessageTell.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "MessageTell.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* MessageTell_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  MessageTell_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_MessageTell_2eproto() {
  protobuf_AddDesc_MessageTell_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "MessageTell.proto");
  GOOGLE_CHECK(file != NULL);
  MessageTell_descriptor_ = file->message_type(0);
  static const int MessageTell_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageTell, token_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageTell, path_),
  };
  MessageTell_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      MessageTell_descriptor_,
      MessageTell::default_instance_,
      MessageTell_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageTell, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageTell, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(MessageTell));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_MessageTell_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    MessageTell_descriptor_, &MessageTell::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_MessageTell_2eproto() {
  delete MessageTell::default_instance_;
  delete MessageTell_reflection_;
}

void protobuf_AddDesc_MessageTell_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\021MessageTell.proto\"*\n\013MessageTell\022\r\n\005To"
    "ken\030\001 \002(\t\022\014\n\004Path\030\002 \002(\t", 63);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "MessageTell.proto", &protobuf_RegisterTypes);
  MessageTell::default_instance_ = new MessageTell();
  MessageTell::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_MessageTell_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_MessageTell_2eproto {
  StaticDescriptorInitializer_MessageTell_2eproto() {
    protobuf_AddDesc_MessageTell_2eproto();
  }
} static_descriptor_initializer_MessageTell_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int MessageTell::kTokenFieldNumber;
const int MessageTell::kPathFieldNumber;
#endif  // !_MSC_VER

MessageTell::MessageTell()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:MessageTell)
}

void MessageTell::InitAsDefaultInstance() {
}

MessageTell::MessageTell(const MessageTell& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:MessageTell)
}

void MessageTell::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  token_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  path_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

MessageTell::~MessageTell() {
  // @@protoc_insertion_point(destructor:MessageTell)
  SharedDtor();
}

void MessageTell::SharedDtor() {
  if (token_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete token_;
  }
  if (path_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete path_;
  }
  if (this != default_instance_) {
  }
}

void MessageTell::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* MessageTell::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MessageTell_descriptor_;
}

const MessageTell& MessageTell::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_MessageTell_2eproto();
  return *default_instance_;
}

MessageTell* MessageTell::default_instance_ = NULL;

MessageTell* MessageTell::New() const {
  return new MessageTell;
}

void MessageTell::Clear() {
  if (_has_bits_[0 / 32] & 3) {
    if (has_token()) {
      if (token_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        token_->clear();
      }
    }
    if (has_path()) {
      if (path_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        path_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool MessageTell::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:MessageTell)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string Token = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_token()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->token().data(), this->token().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "token");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_Path;
        break;
      }

      // required string Path = 2;
      case 2: {
        if (tag == 18) {
         parse_Path:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_path()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->path().data(), this->path().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "path");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:MessageTell)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:MessageTell)
  return false;
#undef DO_
}

void MessageTell::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:MessageTell)
  // required string Token = 1;
  if (has_token()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->token().data(), this->token().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "token");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->token(), output);
  }

  // required string Path = 2;
  if (has_path()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->path().data(), this->path().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "path");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->path(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:MessageTell)
}

::google::protobuf::uint8* MessageTell::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:MessageTell)
  // required string Token = 1;
  if (has_token()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->token().data(), this->token().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "token");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->token(), target);
  }

  // required string Path = 2;
  if (has_path()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->path().data(), this->path().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "path");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->path(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:MessageTell)
  return target;
}

int MessageTell::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string Token = 1;
    if (has_token()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->token());
    }

    // required string Path = 2;
    if (has_path()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->path());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void MessageTell::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const MessageTell* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const MessageTell*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void MessageTell::MergeFrom(const MessageTell& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_token()) {
      set_token(from.token());
    }
    if (from.has_path()) {
      set_path(from.path());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void MessageTell::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MessageTell::CopyFrom(const MessageTell& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MessageTell::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void MessageTell::Swap(MessageTell* other) {
  if (other != this) {
    std::swap(token_, other->token_);
    std::swap(path_, other->path_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata MessageTell::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = MessageTell_descriptor_;
  metadata.reflection = MessageTell_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
