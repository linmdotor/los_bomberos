using UnityEngine;
using System.Collections;

/// <summary>
/// Manages the turret tool
/// 
/// This script must be attach to the turret GameObject
/// 
/// This script is call by the player by its method 'activeTurret'
/// 
/// Version 1:
///     Only one turret allowed
///     If a turret is already placed, it will be moved to the new position
///     The turret last 'm_turretDurationInSeconds' seconds
///     
///     Does not care about enought space por positionate it
/// 
/// </summary>
/// <autor>Xarkos</autor>
public class Turret : MonoBehaviour {

    public float m_turretDurationInSeconds; // The duration of the turret
    public Vector2 m_positionOffset; // The offset from the player, to positionate the turret. Y for forward offset, X for sideshift offset

    public GameObject m_axis; // The element that rotates to target the fire
    public float m_rotationSpeed = 45; // The speed of rotation. Degrees/second

    private float m_deltaTime; // The time the turret has been active
    private Quaternion m_axisInitRot; // The initial rotation of the axis

    /// <summary>
    /// Activates the Turret
    /// </summary>
    /// <param name="place">The place to positionate the turret </param>
    public void activeTurret(Transform place) {
        gameObject.transform.parent = null;

        gameObject.SetActive(true);

        transform.position = place.position + place.forward * m_positionOffset.y + place.right * m_positionOffset.x;
        transform.rotation = place.rotation;
        m_axis.transform.localRotation = m_axisInitRot;

        m_deltaTime = 0.0f;
	}

    void Awake()
    {
        m_axisInitRot = m_axis.transform.localRotation;
    }

    // Updates this instance
    void Update()
    {
        // Update the time
        if (m_turretDurationInSeconds > 0 && !float.IsInfinity(m_turretDurationInSeconds))
        {
            m_deltaTime += Time.deltaTime;
            if (m_deltaTime >= m_turretDurationInSeconds)
                gameObject.SetActive(false);
        }

        // Rotates the axis of the turret
        m_axis.transform.Rotate(Vector3.up,m_rotationSpeed * Time.deltaTime,Space.World);

        BroadcastMessage("startShooting",SendMessageOptions.DontRequireReceiver);
    }

}
