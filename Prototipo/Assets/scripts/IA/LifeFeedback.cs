using UnityEngine;
using System.Collections;

/// <summary>
/// Manages an indicator for the life
/// 
/// It needs an indicator attached to the public variable 'm_lifeIndicator'.
/// 
/// The script will use the x local scale of the Indicator to show the life
/// </summary>
/// <autor>Xarkos</autor>
[RequireComponent(typeof(Life))]
public class LifeFeedback : MonoBehaviour {

    private Life m_life; // The life script attach to this gameObject
    private float m_maxLife; // The maximum life of this gameObject

    public GameObject m_lifeIndicator; // The life Indicator
    private float m_initScale; // The initial scale.x of the Indicator

    void Awake()
    {
        m_life = GetComponent<Life>();
        m_maxLife = m_life.getMaxLife();

        m_lifeIndicator.SetActive(false);

        m_initScale = m_lifeIndicator.transform.localScale.x;
    }

    public bool OnDamage(float damage){

        m_lifeIndicator.SetActive(true);

        // Calculates the life percentage
        float lifePercent = m_life.getLife() / m_maxLife;

        // Scales the sprite by the lifePercent
        Vector3 indicatorScale = m_lifeIndicator.transform.localScale;
        indicatorScale.x = m_initScale * lifePercent;
        m_lifeIndicator.transform.localScale = indicatorScale;

        return true;
    }

    /* Old version: this instantiates the lifeIndicator from a prefab
    private void instanciateLifeSprite()
    {
        if (m_lifeSprite == null)
        {
            m_lifeSprite = Instantiate<GameObject>(m_lifeIndicatorPrefab); // Instantiate the life sprite
            m_lifeSprite.transform.parent = transform; // Set it a children of this gameObject
            m_lifeSprite.transform.localPosition = m_lifeIndicatorPrefab.transform.localPosition; // Resets its position
            m_lifeSprite.transform.localRotation = m_lifeIndicatorPrefab.transform.localRotation; // Resets its rotation
            m_lifeSprite.transform.localScale = m_lifeIndicatorPrefab.transform.localScale; // Resets its scale

            // Give values to some variables
            m_initScale = m_lifeSprite.gameObject.transform.localScale.x;
        }
    }*/ 
}
