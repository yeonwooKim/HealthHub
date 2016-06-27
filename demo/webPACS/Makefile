# Copyright (c) 2013 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

# GNU Makefile based on shared rules provided by the Native Client SDK.
# See README.Makefiles for more details.

VALID_TOOLCHAINS := pnacl glibc clang-newlib mac

NACL_SDK_ROOT ?= $(abspath $(CURDIR)/../../..)

TARGET = graphics_2d


include $(NACL_SDK_ROOT)/tools/common.mk


LIBS = ppapi_cpp ppapi pthread

CFLAGS = -Wall
SOURCES = \
					graphics_2d.cc	\
					gdcm_library/Source/Common/gdcmASN1.cxx	\
					gdcm_library/Source/Common/gdcmBase64.cxx	\
					gdcm_library/Source/Common/gdcmBoxRegion.cxx	\
					gdcm_library/Source/Common/gdcmByteSwap.cxx	\
					gdcm_library/Source/Common/gdcmCAPICryptoFactory.cxx	\
					gdcm_library/Source/Common/gdcmCAPICryptographicMessageSyntax.cxx	\
					gdcm_library/Source/Common/gdcmCommand.cxx	\
          gdcm_library/Source/Common/gdcmCryptoFactory.cxx	\
          gdcm_library/Source/Common/gdcmCryptographicMessageSyntax.cxx	\
          gdcm_library/Source/Common/gdcmDataEvent.cxx	\
          gdcm_library/Source/Common/gdcmDeflateStream.cxx	\
          gdcm_library/Source/Common/gdcmDirectory.cxx	\
          gdcm_library/Source/Common/gdcmDummyValueGenerator.cxx	\
          gdcm_library/Source/Common/gdcmEvent.cxx	\
          gdcm_library/Source/Common/gdcmException.cxx	\
          gdcm_library/Source/Common/gdcmFileNameEvent.cxx	\
          gdcm_library/Source/Common/gdcmFilename.cxx	\
          gdcm_library/Source/Common/gdcmFilenameGenerator.cxx	\
          gdcm_library/Source/Common/gdcmMD5.cxx	\
          gdcm_library/Source/Common/gdcmObject.cxx	\
          gdcm_library/Source/Common/gdcmOpenSSLCryptoFactory.cxx	\
          gdcm_library/Source/Common/gdcmOpenSSLCryptographicMessageSyntax.cxx	\
          gdcm_library/Source/Common/gdcmOpenSSLP7CryptoFactory.cxx	\
          gdcm_library/Source/Common/gdcmOpenSSLP7CryptographicMessageSyntax.cxx	\
          gdcm_library/Source/Common/gdcmProgressEvent.cxx	\
          gdcm_library/Source/Common/gdcmRegion.cxx	\
          gdcm_library/Source/Common/gdcmSHA1.cxx	\
          gdcm_library/Source/Common/gdcmString.cxx	\
          gdcm_library/Source/Common/gdcmSubject.cxx	\
          gdcm_library/Source/Common/gdcmSwapCode.cxx	\
          gdcm_library/Source/Common/gdcmSystem.cxx	\
          gdcm_library/Source/Common/gdcmTerminal.cxx	\
          gdcm_library/Source/Common/gdcmTesting.cxx	\
          gdcm_library/Source/Common/gdcmTrace.cxx	\
          gdcm_library/Source/Common/gdcmUnpacker12Bits.cxx	\
          gdcm_library/Source/Common/gdcmVersion.cxx	\
          gdcm_library/Source/DataDictionary/gdcmDefaultDicts.cxx	\
          gdcm_library/Source/DataDictionary/gdcmDefaultGroupNames.cxx	\
          gdcm_library/Source/DataDictionary/gdcmDictConverter.cxx	\
          gdcm_library/Source/DataDictionary/gdcmDictEntry.cxx	\
          gdcm_library/Source/DataDictionary/gdcmDicts.cxx	\
          gdcm_library/Source/DataDictionary/gdcmGlobal.cxx	\
          gdcm_library/Source/DataDictionary/gdcmGroupDict.cxx	\
          gdcm_library/Source/DataDictionary/gdcmPrepDict.cxx	\
          gdcm_library/Source/DataDictionary/gdcmPrepGroupName.cxx	\
          gdcm_library/Source/DataDictionary/gdcmPrivateDefaultDicts.cxx	\
          gdcm_library/Source/DataDictionary/gdcmRoot.cxx	\
          gdcm_library/Source/DataDictionary/gdcmSOPClassUIDToIOD.cxx	\
          gdcm_library/Source/DataDictionary/gdcmUIDs.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmByteSwapFilter.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmByteValue.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmCP246ExplicitDataElement.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmCSAHeader.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmCodeString.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmDataElement.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmDataSet.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmDataSetEvent.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmExplicitDataElement.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmExplicitImplicitDataElement.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmFile.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmFileMetaInformation.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmFileSet.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmFragment.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmImplicitDataElement.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmItem.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmMediaStorage.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmPDBHeader.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmParseException.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmParser.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmPreamble.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmPrivateTag.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmReader.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmReader.strict.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmSequenceOfFragments.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmSequenceOfItems.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmTag.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmTagToVR.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmTransferSyntax.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmUNExplicitDataElement.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmUNExplicitImplicitDataElement.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmVM.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmVR.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmVR16ExplicitDataElement.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmValue.cxx	\
          gdcm_library/Source/DataStructureAndEncodingDefinition/gdcmWriter.cxx	\
          gdcm_library/Source/InformationObjectDefinition/gdcmDefinedTerms.cxx	\
          gdcm_library/Source/InformationObjectDefinition/gdcmDefs.cxx	\
          gdcm_library/Source/InformationObjectDefinition/gdcmEnumeratedValues.cxx	\
          gdcm_library/Source/InformationObjectDefinition/gdcmIOD.cxx	\
          gdcm_library/Source/InformationObjectDefinition/gdcmIODEntry.cxx	\
          gdcm_library/Source/InformationObjectDefinition/gdcmMacro.cxx	\
          gdcm_library/Source/InformationObjectDefinition/gdcmMacros.cxx	\
          gdcm_library/Source/InformationObjectDefinition/gdcmModule.cxx	\
          gdcm_library/Source/InformationObjectDefinition/gdcmModules.cxx	\
          gdcm_library/Source/InformationObjectDefinition/gdcmNestedModuleEntries.cxx	\
          gdcm_library/Source/InformationObjectDefinition/gdcmPatient.cxx	\
          gdcm_library/Source/InformationObjectDefinition/gdcmSeries.cxx	\
          gdcm_library/Source/InformationObjectDefinition/gdcmStudy.cxx	\
          gdcm_library/Source/InformationObjectDefinition/gdcmTable.cxx	\
          gdcm_library/Source/InformationObjectDefinition/gdcmTableReader.cxx	\
          gdcm_library/Source/InformationObjectDefinition/gdcmType.cxx	\
          gdcm_library/Source/InformationObjectDefinition/gdcmUsage.cxx	\
          gdcm_library/Source/InformationObjectDefinition/gdcmXMLDictReader.cxx	\
          gdcm_library/Source/InformationObjectDefinition/gdcmXMLPrivateDictReader.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmAnonymizeEvent.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmAnonymizer.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmApplicationEntity.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmAudioCodec.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmBitmap.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmBitmapToBitmapFilter.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmCurve.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmDICOMDIR.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmDICOMDIRGenerator.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmDataSetHelper.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmDeltaEncodingCodec.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmDictPrinter.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmDirectionCosines.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmDirectoryHelper.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmDumper.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmEncapsulatedDocument.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmFiducials.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmFileAnonymizer.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmFileChangeTransferSyntax.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmFileDecompressLookupTable.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmFileDerivation.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmFileExplicitFilter.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmFileStreamer.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmIPPSorter.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmIconImage.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmIconImageFilter.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmIconImageGenerator.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmImage.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmImageApplyLookupTable.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmImageChangePhotometricInterpretation.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmImageChangePlanarConfiguration.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmImageChangeTransferSyntax.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmImageCodec.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmImageConverter.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmImageFragmentSplitter.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmImageHelper.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmImageReader.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmImageRegionReader.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmImageToImageFilter.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmImageWriter.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmJPEG12Codec.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmJPEG16Codec.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmJPEG2000Codec.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmJPEG8Codec.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmJPEGBITSCodec.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmJPEGCodec.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmJPEGLSCodec.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmJSON.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmKAKADUCodec.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmLookupTable.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmMeshPrimitive.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmOrientation.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmOverlay.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmPDFCodec.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmPGXCodec.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmPNMCodec.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmPVRGCodec.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmPersonName.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmPhotometricInterpretation.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmPixelFormat.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmPixmap.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmPixmapReader.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmPixmapToPixmapFilter.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmPixmapWriter.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmPrinter.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmRAWCodec.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmRLECodec.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmRescaler.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmScanner.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmSegment.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmSegmentHelper.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmSegmentReader.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmSegmentWriter.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmSegmentedPaletteColorLookupTable.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmSerieHelper.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmSimpleSubjectWatcher.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmSorter.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmSpacing.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmSpectroscopy.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmSplitMosaicFilter.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmStreamImageReader.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmStreamImageWriter.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmStrictScanner.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmStringFilter.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmSurface.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmSurfaceHelper.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmSurfaceReader.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmSurfaceWriter.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmTagPath.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmUIDGenerator.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmUUIDGenerator.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmValidate.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmWaveform.cxx	\
          gdcm_library/Source/MediaStorageAndFileFormat/gdcmXMLPrinter.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmAAbortPDU.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmAAssociateACPDU.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmAAssociateRJPDU.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmAAssociateRQPDU.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmARTIMTimer.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmAReleaseRPPDU.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmAReleaseRQPDU.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmAbstractSyntax.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmApplicationContext.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmAsynchronousOperationsWindowSub.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmBaseQuery.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmBaseRootQuery.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmCEchoMessages.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmCFindMessages.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmCMoveMessages.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmCStoreMessages.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmCommandDataSet.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmCompositeMessageFactory.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmCompositeNetworkFunctions.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmFindPatientRootQuery.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmFindStudyRootQuery.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmImplementationClassUIDSub.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmImplementationUIDSub.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmImplementationVersionNameSub.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmMaximumLengthSub.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmModalityPerformedProcedureStepCreateQuery.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmModalityPerformedProcedureStepSetQuery.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmMovePatientRootQuery.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmMoveStudyRootQuery.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmNActionMessages.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmNCreateMessages.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmNDeleteMessages.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmNEventReportMessages.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmNGetMessages.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmNSetMessages.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmNormalizedMessageFactory.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmNormalizedNetworkFunctions.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmPDUFactory.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmPDataTFPDU.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmPresentationContext.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmPresentationContextAC.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmPresentationContextGenerator.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmPresentationContextRQ.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmPresentationDataValue.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmQueryBase.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmQueryFactory.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmQueryImage.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmQueryPatient.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmQuerySeries.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmQueryStudy.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmRoleSelectionSub.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmSOPClassExtendedNegociationSub.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmServiceClassApplicationInformation.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmServiceClassUser.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmTransferSyntaxSub.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmULActionAA.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmULActionAE.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmULActionAR.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmULActionDT.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmULBasicCallback.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmULConnection.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmULConnectionInfo.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmULConnectionManager.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmULTransitionTable.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmULWritingCallback.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmUserInformation.cxx	\
          gdcm_library/Source/MessageExchangeDefinition/gdcmWLMFindQuery.cxx
# Build rules generated by macros from common.mk:

$(foreach src,$(SOURCES),$(eval $(call COMPILE_RULE,$(src),$(CFLAGS))))

# The PNaCl workflow uses both an unstripped and finalized/stripped binary.
# On NaCl, only produce a stripped binary for Release configs (not Debug).
ifneq (,$(or $(findstring pnacl,$(TOOLCHAIN)),$(findstring Release,$(CONFIG))))
$(eval $(call LINK_RULE,$(TARGET)_unstripped,$(SOURCES),$(LIBS),$(DEPS)))
$(eval $(call STRIP_RULE,$(TARGET),$(TARGET)_unstripped))
else
$(eval $(call LINK_RULE,$(TARGET),$(SOURCES),$(LIBS),$(DEPS)))
endif

$(eval $(call NMF_RULE,$(TARGET),))
