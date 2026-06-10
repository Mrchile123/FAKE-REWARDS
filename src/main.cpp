#include <Geode/Bindings.hpp>
#include <Geode/modify/GameManager.hpp>
#include <Geode/loader/SettingEvent.hpp>

using namespace geode::prelude;

// 1. Modificamos el GameManager para alterar las estadísticas visuales
class $modify(GameManager) {
    
    int getStat(char const* statID) {
        // Revisamos si el usuario activó el interruptor en los ajustes del mod
        bool fakeEnabled = Mod::get()->getSettingValue<bool>("enable-fake-stats");

        if (fakeEnabled) {
            std::string id(statID);
            
            // Si el juego pregunta por las estrellas (stat "6") o diamantes (stat "14")
            if (id == "6") return 999999;  // Estrellas falsas
            if (id == "14") return 888888; // Diamantes falsos
            if (id == "22") return 777777; // Lunas falsas (si estás en 2.2+)
        }

        // Si la opción está apagada, devuelve los valores reales del jugador
        return GameManager::getStat(statID);
    }
};

// 2. Forzar el Safe Mode de Geode si el mod está activo
// Esto evita que las stats falsas se suban a los servidores de RobTop
$execute {
    // Escuchamos cuando el usuario cambia la configuración
    listenForSettingChanges("enable-fake-stats", [](bool enabled) {
        if (enabled) {
            // Activamos el Safe Mode de Geode
            Geode::get()->setSafeMode(true);
            FLAlertLayer::create(
                "Modo Seguro", 
                "¡Stats Falsas Activadas! El Safe Mode de Geode se ha encendido para proteger tu cuenta.", 
                "Entendido"
            )->show();
        } else {
            // Desactivamos el Safe Mode al apagar el mod
            Geode::get()->setSafeMode(false);
        }
    });
}
