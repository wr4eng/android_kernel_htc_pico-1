#ifndef _ASM_ARM_TOPOLOGY_H
#define _ASM_ARM_TOPOLOGY_H

#ifdef CONFIG_ARM_CPU_TOPOLOGY

#include <linux/cpumask.h>

struct cputopo_arm {
	int id;
	int thread_id;
	int core_id;
	int socket_id;
	cpumask_t thread_sibling;
	cpumask_t core_sibling;
};

extern struct cputopo_arm cpu_topology[NR_CPUS];

#define topology_physical_package_id(cpu)	(cpu_topology[cpu].socket_id)
#define topology_core_id(cpu)		(cpu_topology[cpu].core_id)
#define topology_core_cpumask(cpu)	(&cpu_topology[cpu].core_sibling)
#define topology_thread_cpumask(cpu)	(&cpu_topology[cpu].thread_sibling)

#define mc_capable()	(cpu_topology[0].socket_id != -1)
#define smt_capable()	(cpu_topology[0].thread_id != -1)

void init_cpu_topology(void);
void store_cpu_topology(unsigned int cpuid);
const struct cpumask *cpu_coregroup_mask(int cpu);

void set_power_scale(unsigned int cpu, unsigned int power);
int topology_register_notifier(struct notifier_block *nb);
int topology_unregister_notifier(struct notifier_block *nb);

#else

static inline void init_cpu_topology(void) { }
static inline void store_cpu_topology(unsigned int cpuid) { }

static inline void set_power_scale(unsigned int cpu, unsigned int power) { }
static inline int topology_register_notifier(struct notifier_block *nb)  { }
static inline int topology_unregister_notifier(struct notifier_block *nb)  { }

#endif

/* Topology notifier event */
#define TOPOLOGY_POSTCHANGE 0

#include <asm-generic/topology.h>

#endif /* _ASM_ARM_TOPOLOGY_H */
