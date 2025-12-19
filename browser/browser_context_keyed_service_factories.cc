/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "unknown/browser/browser_context_keyed_service_factories.h"

#include "base/feature_list.h"
#include "unknown/browser/brave_account/brave_account_service_factory.h"
#include "unknown/browser/brave_adaptive_captcha/brave_adaptive_captcha_service_factory.h"
#include "unknown/browser/brave_ads/ads_service_factory.h"
#include "unknown/browser/brave_news/brave_news_controller_factory.h"
#include "unknown/browser/brave_origin/brave_origin_service_factory.h"
#include "unknown/browser/brave_rewards/rewards_service_factory.h"
#include "unknown/browser/brave_search/backup_results_service_factory.h"
#include "unknown/browser/brave_shields/ad_block_pref_service_factory.h"
#include "unknown/browser/brave_shields/brave_farbling_service_factory.h"
#include "unknown/browser/brave_shields/brave_shields_settings_service_factory.h"
#include "unknown/browser/debounce/debounce_service_factory.h"
#include "unknown/browser/email_aliases/email_aliases_service_factory.h"
#include "unknown/browser/ephemeral_storage/ephemeral_storage_service_factory.h"
#include "unknown/browser/misc_metrics/profile_misc_metrics_service_factory.h"
#include "unknown/browser/ntp_background/view_counter_service_factory.h"
#include "unknown/browser/permissions/permission_lifetime_manager_factory.h"
#include "unknown/browser/playlist/playlist_service_factory.h"
#include "unknown/browser/profiles/brave_renderer_updater_factory.h"
#include "unknown/browser/search_engines/search_engine_provider_service_factory.h"
#include "unknown/browser/search_engines/search_engine_tracker.h"
#include "unknown/browser/skus/skus_service_factory.h"
#include "unknown/browser/sync/brave_sync_alerts_service_factory.h"
#include "unknown/browser/url_sanitizer/url_sanitizer_service_factory.h"
#include "unknown/browser/webcompat_reporter/webcompat_reporter_service_factory.h"
#include "unknown/components/ai_chat/core/common/buildflags/buildflags.h"
#include "unknown/components/brave_account/features.h"
#include "unknown/components/brave_perf_predictor/browser/named_third_party_registry_factory.h"
#include "unknown/components/brave_vpn/common/buildflags/buildflags.h"
#include "unknown/components/brave_wallet/common/buildflags/buildflags.h"
#include "unknown/components/commander/common/buildflags/buildflags.h"
#include "unknown/components/email_aliases/features.h"
#include "unknown/components/playlist/core/common/features.h"
#include "unknown/components/request_otr/common/buildflags/buildflags.h"
#include "unknown/components/speedreader/common/buildflags/buildflags.h"
#include "unknown/components/tor/buildflags/buildflags.h"
#include "unknown/components/web_discovery/buildflags/buildflags.h"

#if BUILDFLAG(ENABLE_AI_CHAT)
#include "unknown/browser/ai_chat/ai_chat_service_factory.h"
#include "unknown/browser/ai_chat/ollama/ollama_service_factory.h"
#include "unknown/browser/ai_chat/tab_tracker_service_factory.h"
#include "unknown/components/ai_chat/content/browser/model_service_factory.h"
#include "unknown/components/ai_chat/core/common/features.h"
#endif

#if BUILDFLAG(ENABLE_BRAVE_VPN)
#include "unknown/browser/brave_vpn/brave_vpn_service_factory.h"
#endif

#if !BUILDFLAG(IS_ANDROID)
#include "unknown/browser/ui/bookmark/bookmark_prefs_service_factory.h"
#include "unknown/browser/ui/commands/accelerator_service_factory.h"
#include "unknown/browser/ui/tabs/shared_pinned_tab_service_factory.h"
#include "unknown/components/commands/common/features.h"
#include "chrome/browser/ui/tabs/features.h"
#else
#include "unknown/browser/brave_shields/filter_list_service_factory.h"
#include "unknown/browser/ntp_background/android/ntp_background_images_bridge.h"
#endif

#if BUILDFLAG(ENABLE_TOR)
#include "unknown/browser/tor/tor_profile_service_factory.h"
#endif

#if BUILDFLAG(ENABLE_COMMANDER)
#include "unknown/browser/ui/commander/commander_service_factory.h"
#include "unknown/components/commander/common/features.h"
#endif

#if defined(TOOLKIT_VIEWS)
#include "unknown/browser/ui/sidebar/sidebar_service_factory.h"
#endif

#if BUILDFLAG(ENABLE_SPEEDREADER)
#include "unknown/browser/speedreader/speedreader_service_factory.h"
#endif

#if BUILDFLAG(ENABLE_REQUEST_OTR)
#include "unknown/browser/request_otr/request_otr_service_factory.h"
#endif

#if BUILDFLAG(ENABLE_WEB_DISCOVERY_NATIVE)
#include "unknown/browser/web_discovery/web_discovery_service_factory.h"
#endif

#if BUILDFLAG(ENABLE_EXTENSIONS)
#include "unknown/browser/extensions/manifest_v2/brave_extensions_manifest_v2_migrator.h"
#endif

#if BUILDFLAG(ENABLE_BRAVE_WALLET)
#include "unknown/browser/brave_wallet/asset_ratio_service_factory.h"
#include "unknown/browser/brave_wallet/brave_wallet_ipfs_service_factory.h"
#include "unknown/browser/brave_wallet/brave_wallet_service_factory.h"
#include "unknown/browser/brave_wallet/meld_integration_service_factory.h"
#include "unknown/browser/brave_wallet/notifications/wallet_notification_service_factory.h"
#include "unknown/browser/brave_wallet/simulation_service_factory.h"
#include "unknown/browser/brave_wallet/swap_service_factory.h"
#endif

namespace brave {

void EnsureBrowserContextKeyedServiceFactoriesBuilt() {
  brave_adaptive_captcha::BraveAdaptiveCaptchaServiceFactory::GetInstance();
  brave_ads::AdsServiceFactory::GetInstance();
  brave_origin::BraveOriginServiceFactory::GetInstance();
  brave_perf_predictor::NamedThirdPartyRegistryFactory::GetInstance();
  brave_rewards::RewardsServiceFactory::GetInstance();
  brave_shields::AdBlockPrefServiceFactory::GetInstance();
  debounce::DebounceServiceFactory::GetInstance();
  brave::URLSanitizerServiceFactory::GetInstance();
  BraveRendererUpdaterFactory::GetInstance();
  SearchEngineProviderServiceFactory::GetInstance();
  misc_metrics::ProfileMiscMetricsServiceFactory::GetInstance();
  BraveFarblingServiceFactory::GetInstance();
#if BUILDFLAG(ENABLE_TOR)
  TorProfileServiceFactory::GetInstance();
#endif
  SearchEngineTrackerFactory::GetInstance();
  ntp_background_images::ViewCounterServiceFactory::GetInstance();

#if !BUILDFLAG(IS_ANDROID)
  BookmarkPrefsServiceFactory::GetInstance();
#else
  brave_shields::FilterListServiceFactory::GetInstance();
  ntp_background_images::NTPBackgroundImagesBridgeFactory::GetInstance();
#endif

  webcompat_reporter::WebcompatReporterServiceFactory::GetInstance();

  brave_news::BraveNewsControllerFactory::GetInstance();

#if BUILDFLAG(ENABLE_BRAVE_WALLET)
  brave_wallet::AssetRatioServiceFactory::GetInstance();
  brave_wallet::MeldIntegrationServiceFactory::GetInstance();
  brave_wallet::SwapServiceFactory::GetInstance();
  brave_wallet::SimulationServiceFactory::GetInstance();
#if !BUILDFLAG(IS_ANDROID)
  brave_wallet::WalletNotificationServiceFactory::GetInstance();
#endif
  brave_wallet::BraveWalletServiceFactory::GetInstance();
  brave_wallet::BraveWalletIpfsServiceFactory::GetInstance();
#endif

#if !BUILDFLAG(IS_ANDROID)
  if (base::FeatureList::IsEnabled(commands::features::kBraveCommands)) {
    commands::AcceleratorServiceFactory::GetInstance();
  }
#endif

#if BUILDFLAG(ENABLE_COMMANDER)
  if (base::FeatureList::IsEnabled(features::kBraveCommander)) {
    commander::CommanderServiceFactory::GetInstance();
  }
#endif

  EphemeralStorageServiceFactory::GetInstance();
  PermissionLifetimeManagerFactory::GetInstance();
  skus::SkusServiceFactory::GetInstance();
#if BUILDFLAG(ENABLE_BRAVE_VPN)
  brave_vpn::BraveVpnServiceFactory::GetInstance();
#endif
  if (base::FeatureList::IsEnabled(playlist::features::kPlaylist)) {
    playlist::PlaylistServiceFactory::GetInstance();
  }
#if BUILDFLAG(ENABLE_REQUEST_OTR)
  request_otr::RequestOTRServiceFactory::GetInstance();
#endif

  BraveSyncAlertsServiceFactory::GetInstance();

#if !BUILDFLAG(IS_ANDROID)
  if (base::FeatureList::IsEnabled(tabs::kBraveSharedPinnedTabs)) {
    SharedPinnedTabServiceFactory::GetInstance();
  }
#endif

#if defined(TOOLKIT_VIEWS)
  sidebar::SidebarServiceFactory::GetInstance();
#endif

#if BUILDFLAG(ENABLE_SPEEDREADER)
  speedreader::SpeedreaderServiceFactory::GetInstance();
#endif

#if BUILDFLAG(ENABLE_AI_CHAT)
  if (ai_chat::features::IsAIChatEnabled()) {
    ai_chat::AIChatServiceFactory::GetInstance();
    ai_chat::ModelServiceFactory::GetInstance();
    ai_chat::OllamaServiceFactory::GetInstance();
    ai_chat::TabTrackerServiceFactory::GetInstance();
  }
#endif

  brave_search::BackupResultsServiceFactory::GetInstance();

#if BUILDFLAG(ENABLE_WEB_DISCOVERY_NATIVE)
  web_discovery::WebDiscoveryServiceFactory::GetInstance();
#endif

  if (brave_account::features::IsBraveAccountEnabled()) {
    brave_account::BraveAccountServiceFactory::GetInstance();
  }

  if (email_aliases::features::IsEmailAliasesEnabled()) {
    email_aliases::EmailAliasesServiceFactory::GetInstance();
  }

#if BUILDFLAG(ENABLE_EXTENSIONS)
  extensions_mv2::ExtensionsManifestV2MigratorFactory::GetInstance();
#endif
  BraveShieldsSettingsServiceFactory::GetInstance();
}

}  // namespace brave
